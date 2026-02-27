CASE := sharp_crested_weir_2d
SERIAL_BIN := weir2d
MPI_BIN := weir2d_mpi
MPI_SRC := _$(CASE).c

# Assume Basilisk source tree is at basilisk/basilisk/src from repo root.
BASILISK ?= $(abspath basilisk/src)
QCC ?= $(BASILISK)/qcc
MPICC ?= mpicc
MPIRUN ?= mpirun
NP ?= 4
CFLAGS ?= -O2 -Wall
BASILISK_INC := -I$(BASILISK)
OMPI_CFLAGS ?= $(shell $(MPICC) --showme:compile 2>/dev/null)
OMPI_LDFLAGS ?= $(shell $(MPICC) --showme:link 2>/dev/null)

.PHONY: serial mpi mpi-fallback run-serial run-mpi clean

serial:
	mkdir -p run
	$(QCC) $(CFLAGS) $(CASE).c -o $(SERIAL_BIN) -lm

mpi:
	mkdir -p run
	CC99=$(MPICC) $(QCC) -D_DARWIN_C_SOURCE -D_MPI=1 -O2 -disable-dimensions $(CASE).c -o $(MPI_BIN) -lm

mpi-fallback:
	mkdir -p run
	$(QCC) -source -D_MPI=1 $(CASE).c -o $(MPI_SRC)
	$(MPICC) $(CFLAGS) $(BASILISK_INC) $(MPI_SRC) -o $(MPI_BIN) -lm

run-serial: serial
	./$(SERIAL_BIN) > run/out.ppm 2> run/log

run-mpi: mpi
	$(MPIRUN) -np $(NP) ./$(MPI_BIN) > run/out_mpi.ppm 2> run/log_mpi

clean:
	rm -f $(SERIAL_BIN) $(MPI_BIN) $(MPI_SRC)
