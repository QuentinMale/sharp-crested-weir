# macOS-friendly Makefile for Basilisk case

BASILISK_SRC = ./basilisk/src

CASE := sharp_crested_weir_2d
SRC  := $(CASE).c
BIN_MPI := $(CASE)_mpi
MPI_SRC := _$(CASE).c

QCC ?= $(BASILISK_SRC)/qcc
MPICC ?= mpicc

CFLAGS  ?= -O2 -Wall
LDFLAGS ?= -lm
MPI_CPPFLAGS ?= $(if $(BASILISK_SRC),-I$(BASILISK_SRC),)
MPI_CFLAGS ?= -D_DARWIN_C_SOURCE

.PHONY: all mpi check check-mpi clean help

all: check check-mpi $(BIN_MPI)

check:
	@test -x "$(QCC)" || command -v "$(QCC)" >/dev/null 2>&1 || { \
	  echo "Error: qcc not found."; \
	  echo "Tried QCC=$(QCC)"; \
	  echo "Install Basilisk and/or set BASILISK_SRC, e.g."; \
	  echo "  export BASILISK_SRC=\$$HOME/basilisk/src"; \
	  echo "Then run: make"; \
	  exit 1; \
	}

check-mpi:
	@command -v "$(MPICC)" >/dev/null 2>&1 || { \
	  echo "Error: mpicc not found."; \
	  echo "Install MPI (e.g. on macOS: brew install open-mpi)."; \
	  exit 1; \
	}

$(BIN_MPI): $(SRC)
	$(QCC) -source -D_MPI=1 "$<"
	$(MPICC) $(CFLAGS) $(MPI_CFLAGS) $(MPI_CPPFLAGS) "$(MPI_SRC)" -o "$@" $(LDFLAGS)

clean:
	rm -f "$(BIN_MPI)" "$(MPI_SRC)"

help:
	@echo "Targets:"
	@echo "  make         Build MPI binary $(BIN_MPI)"
	@echo "  make mpi     Build MPI binary $(BIN_MPI)"
	@echo "  make clean   Remove generated files"
	@echo ""
	@echo "Optional env vars:"
	@echo "  BASILISK_SRC=/path/to/basilisk/src"
	@echo "  QCC=/path/to/qcc"
	@echo "  MPICC=/path/to/mpicc"
	@echo "  MPI_CPPFLAGS='-I/path/to/basilisk/src'"
	@echo "  CFLAGS='-O2 -Wall'"
