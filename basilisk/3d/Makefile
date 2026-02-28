CASE := sharp_crested_weir_3d
MPI_BIN := weir3d_mpi
MPI_SRC := _$(CASE).c

# Assume Basilisk source tree is at basilisk/basilisk/src from repo root.
BASILISK ?= $(abspath ../basilisk/src)
QCC ?= $(BASILISK)/qcc
MPICC ?= mpicc
MPIRUN ?= mpirun
NP ?= 4
CFLAGS ?= -O2 -Wall
BASILISK_INC := -I$(BASILISK)
OMPI_CFLAGS ?= $(shell $(MPICC) --showme:compile 2>/dev/null)
OMPI_LDFLAGS ?= $(shell $(MPICC) --showme:link 2>/dev/null)
DEFAULT_GOAL := mpi

.PHONY: mpi mpi-fallback run-mpi clean

all: $(DEFAULT_GOAL)

mpi:
	mkdir -p run
	CC99=$(MPICC) $(QCC) -D_DARWIN_C_SOURCE -D_MPI=1 -O2 -disable-dimensions $(CASE).c -o $(MPI_BIN) -lm

mpi-fallback:
	mkdir -p run
	$(QCC) -source -D_MPI=1 $(CASE).c -o $(MPI_SRC)
	$(MPICC) $(CFLAGS) $(BASILISK_INC) $(MPI_SRC) -o $(MPI_BIN) -lm

run-mpi: mpi
	$(MPIRUN) -np $(NP) ./$(MPI_BIN) > run/out_mpi.ppm 2> run/log_mpi

clean:
	rm -f $(MPI_BIN) $(MPI_SRC)
