#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "navier-stokes/conserving.h"
#include "tension.h"
#include "xdmf2d.h"


enum { walllevel = 4, minlevel = 5, maxlevel = 8 };
static double t_end = 30;

static int bulk(double x, double y) { return x < 0.9; }

static const double w_x0 = 0.5, w_x1 = 0.51;
static const double w_y0 = 0.0, w_y1 = 0.250;
static const double u_in = 0.2;
static const double h_in = 0.28;
static double box(double x, double y) {
  double cx, cy, hx, hy, qx, qy, ox, oy, outside, inside;
  cx = 0.5 * (w_x0 + w_x1);
  cy = 0.5 * (w_y0 + w_y1);
  hx = 0.5 * (w_x1 - w_x0);
  hy = 0.5 * (w_y1 - w_y0);
  qx = fabs(x - cx) - hx;
  qy = fabs(y - cy) - hy;
  ox = fmax(qx, 0.0);
  oy = fmax(qy, 0.0);
  outside = hypot(ox, oy);
  inside = fmin(fmax(qx, qy), 0.0);
  return outside + inside;
}

static double levelset(double x, double y) { return x < w_x0 && y < h_in; }

int main(void) {
  rho1 = 10.;
  rho2 = 1.2;
  mu1 = 1e-3;
  mu2 = 1.8e-5;
  f.sigma = 7.2e-2;
  G.y = -9.81;
  run();
}

u.n[bottom] = dirichlet(0);
u.t[bottom] = dirichlet(0);

u.n[left] = dirichlet(y < h_in ? u_in : 0.);
u.t[left] = dirichlet(0);
p[left] = neumann(0);
pf[left] = neumann(0);
f[left] = dirichlet(y < h_in ? 1. : 0.);

u.n[right] = dirichlet(max(0., u.n[]));
u.t[right] = neumann(0);
p[right] = dirichlet(0);
pf[right] = dirichlet(0);
f[right] = neumann(0);

u.n[embed] = dirichlet(0);
u.t[embed] = dirichlet(0);

event init(t = 0) {
  init_grid(1 << walllevel);
  refine(bulk(x, y) && level < minlevel);
  refine( 0 < box(x, y) && box(x, y) < 0.025 && level < maxlevel);
  solid(cs, fs, box(x, y));
  foreach () {
    u.x[] = 0;
    u.y[] = 0;
  }
  fraction(f, levelset(x, y));
}

event adapt(i++) {
  adapt_wavelet((scalar *){f, u}, (double[]){1e-3, 5e-3, 5e-3}, maxlevel,
                minlevel);
}

event xdmf_output(t += 0.1) {
  char prefix[FILENAME_MAX];
  int tid = (int)(t * 1e3 + 0.5);
  fields_stats();
  sprintf(prefix, "run/weir-%06d", tid);
  output_xdmf(t, {f, p, cs}, {u}, NULL, prefix);
}

event end(t = t_end) {}
