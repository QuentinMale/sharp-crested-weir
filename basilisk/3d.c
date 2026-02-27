#include "grid/octree.h"
#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "navier-stokes/conserving.h"
#include "tension.h"
#include "xdmf3d.h"

/*
  CC99=mpicc qcc -D_DARWIN_C_SOURCE -D_MPI=1 -O2 -disable-dimensions 3d.c
  mpiexec ./a.out
 */
enum { walllevel = 4, minlevel = 5, maxlevel = 6 };
static double t_end = 10;

static double levelset(double x, double y) { return x < 0.250 && y < 0.75; }
static int bulk(double x, double y) { return x < 0.9; }
static struct Box {
   double x0, x1, y0, y1, z0, z1;
} boxes[] =
  {{0.250, 0.375, 0.000, 0.500, 0.000, 0.250},
   {0.250, 0.375, 0.000, 0.250, 0.250, 0.750},
   {0.250, 0.375, 0.000, 0.500, 0.750, 1.000},
  };

static double box0(struct Box *b, double x, double y, double z)
{
  double cx, cy, cz, hx, hy, hz;
  double qx, qy, qz, ox, oy, oz;
  double outside, inside;

  cx = 0.5 * (b->x0 + b->x1);
  cy = 0.5 * (b->y0 + b->y1);
  cz = 0.5 * (b->z0 + b->z1);

  hx = 0.5 * (b->x1 - b->x0);
  hy = 0.5 * (b->y1 - b->y0);
  hz = 0.5 * (b->z1 - b->z0);

  qx = fabs(x - cx) - hx;
  qy = fabs(y - cy) - hy;
  qz = fabs(z - cz) - hz;

  ox = fmax(qx, 0.0);
  oy = fmax(qy, 0.0);
  oz = fmax(qz, 0.0);

  outside = sqrt(ox*ox + oy*oy + oz*oz);
  inside  = fmin(fmax(fmax(qx, qy), qz), 0.0);

  return outside + inside;
}
static double box(double x, double y, double z) {
  double ans;
  int i;
  ans = DBL_MAX;
  for (i = 0; i < sizeof boxes / sizeof *boxes; i++)
    ans = fmin(ans, box0(&boxes[i], x, y, z));
  return ans;
}

int main(void) {
  rho1 = 1;
  rho2 = 10;
  mu1 = 1e-5;
  mu2 = 1e-5;
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
  refine( 0 < box(x, y, z) && box(x, y, z) < 0.025 && level < maxlevel);
  solid(cs, fs, box(x, y, z));
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
