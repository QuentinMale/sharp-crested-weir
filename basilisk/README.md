# 2D Sharp-Crested Weir (Basilisk)

This case sets up a 2D water-air simulation of overflow over a thin sharp-crested weir using Basilisk.

## Files

- `sharp_crested_weir_2d.c`: Basilisk case file.
- `weir_timeseries.csv`: generated at runtime (upstream head and discharge).
- `dump-*`: generated snapshots for post-processing/restart.

## Physical model

- Incompressible two-phase flow (water + air)
- Gravity-driven overflow
- Embedded boundary for the weir plate
- Adaptive quadtree mesh refinement

## Install Basilisk source (macOS)

If `qcc` is not available yet, install/build Basilisk first:

```bash
brew install darcs gawk make
darcs clone https://basilisk.fr/basilisk
cd basilisk/src
ln -sf config.osx config
make clean
make
```

## Build this case

```bash
make BASILISK_SRC="./basilisk/basilisk/src"
```

Then run the executable manually:

```bash
./sharp_crested_weir_2d 2> log.txt
```

## Main parameters (in `sharp_crested_weir_2d.c`)

- `crest_height`: weir crest elevation above channel bottom
- `weir_x`: weir x-position
- `weir_thickness`: plate thickness
- `h_up_init`: initial upstream water depth
- `h_down_init`: initial downstream water depth
- `maxlevel`: max AMR level

## Output

The run writes:

- `weir_timeseries.csv` with columns: `t,h_up,q,h_over_p`
- progress lines to `stderr` (redirected to `log.txt` in the command above)

Use `q` with `h_up` to estimate a discharge coefficient relation versus `h/p`.
