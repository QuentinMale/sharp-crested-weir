# 2D Sharp-Crested Weir (Basilisk)

This folder contains a 2D VOF/two-phase Basilisk setup for flow over a sharp-crested weir, with serial and MPI build/run targets.

## Files

- `sharp_crested_weir_2d.c`: main Basilisk case.
- `Makefile`: serial/MPI compile and run targets.
- `output_xdmf.h`: helper for XDMF output in MPI mode.
- `run/`: generated outputs (`log`, `log_mpi`, `weir_timeseries.csv`, `dump-*`, XDMF files).

## Basilisk source location

The Makefile assumes Basilisk source is in:

- `basilisk/src`

i.e. `qcc` is expected at:

- `basilisk/src/qcc`

## Build and run

From this directory:

```bash
make serial
make run-serial
```

MPI:

```bash
make mpi
make run-mpi NP=4
```

If direct `qcc -D_MPI=1` linking fails on your machine, use:

```bash
make mpi-fallback
```

## Model summary

- Solver: `navier-stokes/centered` + `two-phase` + `embed` on quadtree grid.
- Geometry: embedded thin vertical weir plate.
- Phases: water (`rho1`, `mu1`) and air (`rho2`, `mu2`).
- Gravity: `G.y = -9.81`.
- Surface tension: `f.sigma = 0.072`.
- Inlet: ramped inflow profile at left boundary.
- Outlet: right boundary with pressure outlet and fixed downstream tailwater (`f[right]`).
- Extra safeguard: right-boundary backflow clamp (`u.x >= 0` at outlet boundary cells).

## AMR behavior

- AMR event runs every 5 iterations.
- Current AMR indicator uses a filtered scalar `famr`:
  - `famr = f` only where `cs > 0.999`, otherwise `0`.
- This guard is used to avoid known MPI crashes in `embed-tree` refinement near cut-cells.
- Levels:
  - `minlevel = 6`
  - `maxlevel = 8`

## Outputs

Standard logs:

- `run/log` (serial stderr)
- `run/log_mpi` (MPI stderr)

Time series:

- `run/weir_timeseries.csv` with:
  - `t,h_up,q,h_over_p`

Restart/snapshots:

- `run/dump-*` and `run/dump-final`

MPI XDMF (every 0.1 s):

- `run/weir-*.xdmf2`
- matching raw arrays `run/weir-*.xyz.raw` and `run/weir-*.attr.raw`

## Notes

- `run/out.ppm` and `run/out_mpi.ppm` capture stdout. They can stay empty if no `output_ppm()` is called.
- If MPI crashes at AMR step with `embed-tree.h` assertions, tighten AMR criteria or keep the `cs > 0.999` AMR filter.
