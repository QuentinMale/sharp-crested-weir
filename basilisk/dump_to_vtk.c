#include "grid/quadtree.h"
#include "embed.h"
#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "reduced.h"
#include "vtk.h"

/*
  Convert a Basilisk dump file to VTK.

  Usage:
    ./dump_to_vtk [dump_file] [vtk_file] [resolution]

  Example:
    ./dump_to_vtk dump-00.200 dump-00.200.vtk 512
*/

int main (int argc, char * argv[])
{
  const char * dump_file = (argc > 1 ? argv[1] : "dump-final");
  const char * vtk_file  = (argc > 2 ? argv[2] : "dump.vtk");
  int n = (argc > 3 ? atoi (argv[3]) : 512);

  if (!restore (file = dump_file)) {
    fprintf (ferr, "Could not restore dump file: %s\n", dump_file);
    return 1;
  }

  FILE * fp = fopen (vtk_file, "w");
  if (!fp) {
    fprintf (ferr, "Could not open VTK output file: %s\n", vtk_file);
    return 1;
  }

  output_vtk ((scalar *) {f, p, u.x, u.y}, n, fp, true);
  fclose (fp);

  fprintf (ferr, "Wrote %s from %s (n=%d)\n", vtk_file, dump_file, n);
  return 0;
}
