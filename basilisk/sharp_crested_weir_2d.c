#include "grid/quadtree.h"
#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "tension.h"
#include "navier-stokes/perfs.h"
#include "output_xdmf.h"
#include <stdlib.h>

/*
  2D sharp-crested weir case (water-air) in Basilisk.

  Geometry:
  - Bottom at y = 0
  - Thin vertical weir plate from y = 0 to y = crest_height
  - Plate spans x in [weir_x, weir_x + weir_thickness]

  Setup:
  - Upstream and downstream initial depths create a head difference
  - Gravity drives overflow above the crest
  - Outputs a time history of upstream head and discharge
*/

// Domain and geometry parameters (SI units)
double channel_length = 2.4;
double channel_height = 0.8;
double crest_height = 0.35;
double weir_x = 1.0;
double weir_thickness = 0.01;
double H_up = 0.55;     // fixed upstream depth (water level)
double h_down_init = 0.3; //0.08;
double x_res = 0.10;    // width of enforced reservoir region
double damp = 8.0;      // velocity damping rate [1/s]

// Numerical controls
int minlevel = 5;
int maxlevel = 9;
double t_end = 6.0;
double dt_output = 0.01;

vertex scalar phi[];

// Build the sharp-crested weir as an embedded solid.
static void build_weir_geometry (void) {
  foreach_vertex() {
    // Finite-height rectangular plate:
    // weir_x <= x <= weir_x + weir_thickness and 0 <= y <= crest_height
    // Inside solid when all terms are <= 0.
    double plate_x = fabs(x - (weir_x + 0.5*weir_thickness)) - 0.5*weir_thickness;
    double plate_top = y - crest_height;
    double plate_bottom = -y;
    phi[] = max(max(plate_x, plate_top), plate_bottom);
  }
  fractions (phi, cs, fs);
  boundary ({cs, fs});
}

int main() {
  size (channel_length);
  origin (0.0, 0.0);
  init_grid (1 << minlevel);

  // Physical properties for water (phase 1) and air (phase 2)
  rho1 = 1000.0;
  rho2 = 1.2;
  mu1 = 1.0e-3;
  mu2 = 1.8e-5;
  f.sigma = 0.0; //0.072;

  // Gravity
  G.y = -9.81;

  run();
}

// Flow boundaries
u.n[left] = neumann(0.);
u.t[left] = neumann(0.);
p[left]   = dirichlet(0.);
pf[left]  = dirichlet(0.);

u.n[bottom] = dirichlet(0.0);
u.t[bottom] = dirichlet(0.0);

// Open outflow on the right
u.n[right] = neumann(0.0);
u.t[right] = neumann(0.);
p[right]   = dirichlet(0.0);
pf[right]  = dirichlet(0.0);

// Open top (atmospheric)
u.n[top] = neumann(0.0);
u.t[top]   = neumann(0.);
p[top]   = dirichlet(0.0);
pf[top]  = dirichlet(0.0);

// No-slip at the embedded weir wall
u.n[embed] = dirichlet(0.0);
u.t[embed] = dirichlet(0.0);

event init (t = 0) {
  system ("mkdir -p output");

  // Keep a rectangular physical domain while using quadtree (square) grid.
#if !_MPI
  mask (y > channel_height ? top : none);
#endif

  build_weir_geometry();

  // Refine around the interface and near the weir at startup.
  refine ((x > weir_x - 0.3 && x < weir_x + 0.5 && y < H_up + 0.2 &&
           level < maxlevel));

  // Initial free surface: higher upstream pool and lower downstream pool.
  fraction (f, x < weir_x ? (H_up - y) : (h_down_init - y));
  foreach()
    f[] = min (f[], cs[]);

  boundary ({f, u.x, u.y});
}

event enforce_reservoir (i++)
{
  foreach() if (x < x_res && cs[] > 0.) {
    // reset to still-water reservoir
    f[] = (y < H_up) ? 1. : 0.;
    u.x[] *= exp(-damp*dt);
    u.y[] *= exp(-damp*dt);
  }
  boundary({f});
  boundary((scalar *){u});
}

event adapt (i++) {
  adapt_wavelet ({f, u.x, u.y}, (double[]){1e-3, 3e-3, 3e-3},
                 maxlevel, minlevel);
}

event logfile (t += dt_output) {
  // Upstream head sample location
  const double x_head = weir_x - 0.15;
  // Discharge sample location downstream of the crest
  const double x_q = weir_x + weir_thickness + 0.05;
  const double band = 2.0 * L0 / (1 << maxlevel);

  double area_head = 0.0;
  double q_int = 0.0;

  foreach (reduction(+:area_head) reduction(+:q_int)) {
    if (fabs(x - x_head) < 0.5*band) {
      area_head += f[]*dv();
    }
    if (fabs(x - x_q) < 0.5*band)
      q_int += f[]*u.x[]*dv();
  }

  // depth = water area / strip width
  double h_head = area_head/band;
  // discharge per unit width = volume flux / strip width
  double q = q_int/band;
  double h_over_p = h_head/crest_height;

  static FILE * fp = NULL;
  if (!fp) {
    fp = fopen ("output/weir_timeseries.csv", "w");
    fprintf (fp, "t,h_up,q,h_over_p\n");
  }
  fprintf (fp, "%g,%g,%g,%g\n", t, h_head, q, h_over_p);
  fflush (fp);

  fprintf (stderr, "t=%g h_up=%g q=%g h/p=%g\n", t, h_head, q, h_over_p);
}

event monitor (i += 20) {
  if (pid() == 0)
    fprintf (stderr,
             "perf i=%d t=%g dt=%g cells=%ld mgp.i=%d mgpf.i=%d mgu.i=%d speed=%g\n",
             i, t, dt, grid->tn, mgp.i, mgpf.i, mgu.i, perf.speed);
}

event snapshot (t += 1.0) {
  char name[80];
  sprintf (name, "output/dump-%06.3f", t);
  dump (file = name);
}

event xdmf_output (t += 0.1) {
  char prefix[80];
  sprintf (prefix, "output/weir-%06.3f", t);
  output_xdmf (t, (scalar *){f, p, cs, phi}, (vector *){u}, NULL, prefix);
}

event stop (t = t_end) {
  dump (file = "output/dump-final");
  if (pid() == 0)
    system ("test -f perfs && mv -f perfs output/perfs");
}
