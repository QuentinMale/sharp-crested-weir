#include "grid/quadtree.h"
#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "tension.h"
#include "navier-stokes/perfs.h"
#if _MPI
#include "output_xdmf.h"
#endif
#include <math.h>
#include <stdlib.h>

/*
  First 2D VOF case: overflow over a sharp-crested weir plate.
  Domain is a long channel with an embedded thin wall from bottom up to crest.
*/

double channel_length = 2.4;
double channel_height = 0.8;
double crest_height = 0.35625; // 38*Delta on a 256-cell grid
double weir_x = 1.0125;        // 108*Delta
double weir_thickness = 0.05625; // 6*Delta
double weir_base = 0.;

double H_up = 0.55;
double h_down_init = 0.20;
double U_in = 0.25;
double T_ramp = 0.5;

int minlevel = 6;
int maxlevel = 8;
double t_end = 6.0;
double dt_output = 0.01;

vertex scalar phi[];

static void build_weir_geometry (void)
{
  foreach_vertex() {
    double plate_x = fabs (x - (weir_x + 0.5*weir_thickness)) - 0.5*weir_thickness;
    double plate_top = y - crest_height;
    double plate_bottom = weir_base - y;
    phi[] = max (max (plate_x, plate_top), plate_bottom);
  }
  fractions (phi, cs, fs);
  // Remove degenerate cut-cells to avoid severe CFL restrictions.
  fractions_cleanup (cs, fs);
  boundary ({cs, fs});
}

int main (void)
{
  size (channel_length);
  origin (0., 0.);
  N = 1 << maxlevel;

  CFL = 0.4;
  DT = 1e-3;

  rho1 = 1000.;
  rho2 = 1.2;
  mu1 = 1e-3;
  mu2 = 1.8e-5;
  f.sigma = 0.072;

  G.y = -9.81;
  Z.y = H_up;

  run();
}

u.n[left] = dirichlet ((t < T_ramp ? t/T_ramp : 1.)*
                       U_in*(y < H_up ? 1. - sq(y/H_up - 1.) : 0.));
u.t[left] = neumann(0.);
p[left]   = neumann(0.);
pf[left]  = neumann(0.);
f[left]   = dirichlet (y < H_up);

u.n[bottom] = dirichlet(0.);
u.t[bottom] = dirichlet(0.);

u.n[right] = neumann(0.);
u.t[right] = neumann(0.);
p[right]   = dirichlet(0.);
pf[right]  = dirichlet(0.);
// Impose downstream tailwater at outlet to prevent domain-wide level drift.
f[right]   = dirichlet (y < h_down_init);

u.n[top] = neumann(0.);
u.t[top] = neumann(0.);
p[top]   = neumann(0.);
pf[top]  = neumann(0.);

u.n[embed] = dirichlet(0.);
u.t[embed] = dirichlet(0.);

event init (t = 0)
{
  system ("mkdir -p run");

  build_weir_geometry();

  for (scalar s in {u, p, pf})
    s.third = true;

  fraction (f, x < weir_x ? (H_up - y) : (h_down_init - y));
  foreach()
    f[] = min (f[], cs[]);

  foreach() {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  boundary ({f, u.x, u.y});
}

event adapt (i += 5)
{
  if (i < 5)
    return 0;

  scalar famr[];
  foreach()
    // Keep AMR away from embed cut-cells (cs ~ 1 only) to avoid MPI embed refinement assertion.
    famr[] = (cs[] > 0.999) ? f[] : 0.;

  astats s = adapt_wavelet ({famr},
                            (double[]){5e-4},
                            maxlevel, minlevel);
  build_weir_geometry();
  foreach()
    f[] = min (f[], cs[]);
  boundary ({f, cs, fs, u.x, u.y, famr});
  if ((s.nf || s.nc) && pid() == 0)
    fprintf (stderr, "amr i=%d t=%g refined=%d coarsened=%d cells=%ld\n",
             i, t, s.nf, s.nc, grid->tn);
}

event logfile (t += dt_output)
{
  const double x_head = weir_x - 0.15;
  const double x_q = weir_x + weir_thickness + 0.05;
  const double band = 2.0*L0/(1 << maxlevel);

  double area_head = 0.;
  double q_int = 0.;

  foreach (reduction(+:area_head) reduction(+:q_int)) {
    if (fabs (x - x_head) < 0.5*band)
      area_head += cs[]*f[]*dv();
    if (fabs (x - x_q) < 0.5*band)
      q_int += cs[]*f[]*u.x[]*dv();
  }

  double h_head = area_head/band;
  double q = q_int/band;
  double h_over_p = h_head/crest_height;

  static FILE * fp = NULL;
  if (!fp) {
    fp = fopen ("run/weir_timeseries.csv", "w");
    fprintf (fp, "t,h_up,q,h_over_p\n");
  }
  fprintf (fp, "%g,%g,%g,%g\n", t, h_head, q, h_over_p);
  fflush (fp);

  fprintf (stderr, "t=%g h_up=%g q=%g h/p=%g\n", t, h_head, q, h_over_p);
}

event monitor (i += 20)
{
  if (pid() == 0)
    fprintf (stderr,
             "perf i=%d t=%g dt=%g cells=%ld mgp.i=%d mgpf.i=%d mgu.i=%d speed=%g\n",
             i, t, dt, grid->tn, mgp.i, mgpf.i, mgu.i, perf.speed);
}

// Enforce a one-way outlet: prevent any backflow entering from the right boundary.
event outlet_guard (i++)
{
  foreach_boundary (right)
    if (u.x[] < 0.)
      u.x[] = 0.;
  boundary ((scalar *){u});
}

event snapshot (t += 1.0)
{
  char name[80];
  sprintf (name, "run/dump-%06.3f", t);
  dump (file = name);
}

#if _MPI
event xdmf_output (t += 0.1)
{
  char prefix[80];
  int tid = (int) (t*1e3 + 0.5);
  sprintf (prefix, "run/weir-%06d", tid);
  output_xdmf (t, (scalar *){f, p, cs}, (vector *){u}, NULL, prefix);
}
#endif

event stop (t = t_end)
{
  dump (file = "run/dump-final");
  if (pid() == 0)
    system ("test -f perfs && mv -f perfs run/perfs");
}
