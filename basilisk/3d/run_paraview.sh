#!/bin/bash
#SBATCH -t 2-00:00          # Runtime in D-HH:MM, minimum of 10 minutes
#SBATCH -p seas_compute
#SBATCH --mem=0           # Memory pool for all cores (see also --mem-per-cpu)
#SBATCH --ntasks=1
#SBATCH --constraint sapphirerapids
#SBATCH --cpus-per-task=8
##SBATCH --exclusive
#SBATCH -o slurm_%j.out  # File to which STDOUT will be written, %j inserts jobid
#SBATCH -e slurm_%j.err  # File to which STDERR will be written, %j inserts jobid

ml load gcc

unset DISPLAY

xvfb-run -s "-screen 0 1920x1080x24" /n/holylabs/koumoutsakos_lab/Lab/qmale/opt/ParaView-5.13.3-MPI-Linux-Python3.10-x86_64/bin/pvbatch --force-offscreen-rendering render.py

