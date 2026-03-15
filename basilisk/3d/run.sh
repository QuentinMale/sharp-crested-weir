#!/bin/bash
#SBATCH -t 2-00:00          # Runtime in D-HH:MM, minimum of 10 minutes
#SBATCH -p seas_compute
#SBATCH --mem=0           # Memory pool for all cores (see also --mem-per-cpu)
#SBATCH --ntasks=32
#SBATCH --constraint sapphirerapids
#SBATCH --cpus-per-task=1
##SBATCH --exclusive
#SBATCH -o slurm_%j.out  # File to which STDOUT will be written, %j inserts jobid
#SBATCH -e slurm_%j.err  # File to which STDERR will be written, %j inserts jobid

ml load gcc openmpi

mkdir -p run
mkdir -p output
mkdir -p checkpoints

CC99=mpicc ./qcc -D_GNU_SOURCE -D_MPI=1 -O2 -disable-dimensions sharp_crested_weir_3d.c -o exec -lm

export OMPI_MCA_coll_hcoll_enable=0
export OMPI_MCA_coll=^hcoll,ml

#export RESTORE=run/checkpoint-000050

srun -u --mpi pmix exec
