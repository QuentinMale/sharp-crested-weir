#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "navier-stokes/conserving.h"
#include "tension.h"
#include "xdmf2d.h"

/*
  CC99=mpicc qcc -D_DARWIN_C_SOURCE -D_MPI=1 -O2 -disable-dimensions 2d.c
  mpiexec ./a.out
 */
enum { walllevel = 4, minlevel = 5, maxlevel = 8 };
static double t_end = 10;

static double levelset(double x, double y) { return x < 0.5 && y < 0.5; }

static int bulk(double x, double y) { return x < 0.9; }

static const double w_x0 = 0.5, w_x1 = 0.625;
static const double w_y0 = 0.0, w_y1 = 0.250;
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

int main(void) {
  rho1 = 1;
  rho2 = 10;
  mu1 = 1e-3;
  mu2 = 1e-3;
  f.sigma = 1e-6;
  G.y = 1;
  run();
}

u.n[bottom] = dirichlet(0);
u.t[bottom] = dirichlet(0);

u.n[right] = neumann(0);
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

event xdmf_output(t += 0.1) {
  char prefix[FILENAME_MAX];
  int tid = (int)(t * 1e3 + 0.5);
  fields_stats();
  sprintf(prefix, "weir-%06d", tid);
  output_xdmf(t, {f, p, cs}, {u}, NULL, prefix);
}

event end(t = t_end) {}
