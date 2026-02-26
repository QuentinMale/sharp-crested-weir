# AGENTS.md - Basilisk workflow for sharp-crested weir

## Goal
Use Basilisk to simulate flow over a sharp-crested weir in this repository, with reproducible setup and execution on macOS.

## Source of truth
- Main site: https://www.basilisk.fr
- Tutorial: https://www.basilisk.fr/Tutorial
- Install docs: https://www.basilisk.fr/src/INSTALL
- Examples index: https://www.basilisk.fr/src/examples/README
- Test index: https://basilisk.fr/src/test/README

## Agent operating rules
- Prefer minimal, incremental edits.
- Keep outputs separated from source files (e.g. `run/`, `results/`, `log/`).
- When introducing new physics/numerics, add a short rationale in comments.

## Basilisk install in current folder (macOS)
1. Install prerequisites (example with Homebrew):
   - `brew install darcs gawk make gcc gnuplot imagemagick ffmpeg`
2. From repository root, clone Basilisk source locally:
   - `darcs clone https://basilisk.fr/basilisk basilisk`
3. Compile Basilisk:
   - `cd basilisk/src`
   - `ln -s config.osx config`
   - `make`

## Recommended starting point for sharp-crested weir
- Start from a nearby free-surface example (e.g. transcritical flow over a bump) and adapt geometry/boundaries to a sharp crest.
- Use a dedicated case file such as `sharp_crested_weir_2d.c`.
- Start in 2D, then refine:
  - baseline uniform grid,
  - fixed-time outputs,
  - adaptive refinement with `adapt_wavelet`.

## Standard compile/run pattern
Use MPI by default.

- Single-process quick check:
  - `qcc -O2 -Wall basilisk/sharp_crested_weir_2d.c -o basilisk/weir2d -lm`
  - `./basilisk/weir2d > basilisk/run/out.ppm 2> basilisk/run/log`

- MPI build and run:
  - `qcc -D_MPI=1 -O2 -Wall basilisk/sharp_crested_weir_2d.c -o basilisk/weir2d_mpi -lm`
  - `mpirun -np 4 ./basilisk/weir2d_mpi > basilisk/run/out_mpi.ppm 2> basilisk/run/log_mpi`

## Makefile requirement
- Prefer a case-local `Makefile` to avoid manual command repetition.
- Minimum targets:
  - `serial` (compile serial executable),
  - `mpi` (compile MPI executable),
  - `run-serial` and `run-mpi` (write stdout/stderr to `basilisk/run/`),
  - `clean`.
- Re-run simulations through make targets, not ad-hoc shell commands.

## Examples

Various equations
- Conway’s game of life
  https://basilisk.fr/src/examples/life.c
- Coupled reaction–diffusion equations: the Brusselator
  https://basilisk.fr/src/examples/brusselator.c
- The complex Ginzburg–Landau equation
  https://basilisk.fr/src/examples/ginzburg-landau.c
- Distance field computation from a 3D model
  https://basilisk.fr/src/examples/distance.c
- Wavelet transforms and filtering
  https://basilisk.fr/src/examples/wavelet.c

Navier–Stokes
- Decaying two-dimensional turbulence
  https://basilisk.fr/src/examples/turbulence.c
- Bénard–von Kármán Vortex Street for flow around a cylinder at Re=160
  https://basilisk.fr/src/examples/karman.c
- Vortex shedding behind a sphere at Re=300
  https://basilisk.fr/src/examples/sphere.c
- Forced isotropic turbulence in a triply-periodic box
  https://basilisk.fr/src/examples/isotropic.c
- Stokes flow through a complex 3D porous medium
  https://basilisk.fr/src/examples/porous3D.c
- Coupling two solvers
  https://basilisk.fr/src/examples/master.c
- Starting vortex of a 2D NACA2414 airfoil at Re=10000
  https://basilisk.fr/src/examples/naca2414-starting.c

Two-phase flows
- Atomisation of a pulsed liquid jet
  https://basilisk.fr/src/examples/atomisation.c
- Bubble rising in a large tank
  https://basilisk.fr/src/examples/bubble.c
- Flow in a rotating bottom-driven cylindrical container
  https://basilisk.fr/src/examples/yang.c
- Two-phase flow around RV Tangaroa
  https://basilisk.fr/src/examples/tangaroa.c

Geophysical applications
- The 2004 Indian Ocean tsunami
  https://basilisk.fr/src/examples/tsunami.c
- The 2011 Tohoku tsunami
  https://basilisk.fr/src/examples/tohoku.c
- Breakup of a rectangular perturbation into a train of solitons
  https://basilisk.fr/src/examples/madsen.c
- Tidally-induced internal lee waves
  https://basilisk.fr/src/examples/lee.c
- Periodic wave propagation over an ellipsoidal shoal
  https://basilisk.fr/src/examples/shoal.c
- Periodic wave propagation over an ellipsoidal shoal (multilayer solver)
  https://basilisk.fr/src/examples/shoal-ml.c
- 3D breaking Stokes wave (multilayer solver)
  https://basilisk.fr/src/examples/breaking.c
- Transcritical flow over a bump
  https://basilisk.fr/src/examples/gaussian-ns.c
- A Shallow Water Analogue for the Standing Accretion Shock Instability
  https://basilisk.fr/src/examples/swasi.c
- The Gulf Stream
  https://basilisk.fr/src/examples/gulf-stream.c
- The Global Oceanic Circulation
  https://basilisk.fr/src/examples/global.c
- Global tides
  https://basilisk.fr/src/examples/global-tides.c

Python interface
- Decaying two-dimensional turbulence
  https://basilisk.fr/src/examples/example.py
- Poisson problem
  https://basilisk.fr/src/examples/poisson.py

See also
- Test cases
  https://basilisk.fr/src/test/README
- Examples by Pierre-Yves Lagrée
  https://basilisk.fr/sandbox/M1EMN/README
- Examples (and more) by Antoon van Hooft
  https://basilisk.fr/sandbox/Antoonvh/README