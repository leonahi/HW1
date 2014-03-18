# Build process for main_serial.cpp, main_openMP.cpp,  main_MPI.cpp(openMPI)
#
# Author: Nahit Pawar
#         M.Tech - Electrical Dept. - IITB
# 
# Date: 18-Mar-2014 

# For main_serial.cpp and main_openMP.cpp
CPP=g++
FLAGS=-fopenmp
MAIN_SERIAL=main_serial.cpp
MAIN_OPENMP=main_openMP.cpp
EXEC_SERIAL=matrix_multiply_serial
EXEC_OPENMP=matrix_multiply_openmp

# For main_MPI.cpp
MPI=mpic++
MPIRUN=mpirun
NP=4
NPFLAG=-np
MAIN_MPI=main_MPI.cpp
EXEC_MPI=matrix_multiply_mpi

RM=rm

.PHONY: all
.PHONY: clean
.PHONY: compile
.PHONY: run
.PHONY: acknowledge

all: serial openmp mpi acknowledge
acknowledge:
	@echo " "
	@echo "Compilation for serial, openmp, mpi done successfully!!"
	@echo " "

serial: compile_serial acknowledge_serial
compile_serial:
	$(CPP) -o $(EXEC_SERIAL) $(MAIN_SERIAL)
acknowledge_serial:
	@echo " "
	@echo "Compilation for serial code (main_serial.cpp) done successfully!!"
	@echo " "

openmp: compile_openmp acknowledge_openmp
compile_openmp:
	$(CPP) -o $(EXEC_OPENMP) $(FLAGS) $(MAIN_OPENMP)
acknowledge_openmp:
	@echo " "
	@echo "Compilation for openmp code (main_openmp.cpp) done successfully!!"
	@echo " "

mpi: compile_mpi acknowledge_mpi
compile_mpi:
	$(MPI) -o $(EXEC_MPI) $(MAIN_MPI)
acknowledge_mpi:
	@echo " "
	@echo "Compilation for mpi code (main_mpi.cpp) done successfully!!"
	@echo " "


# Run process
run_mpi: $(EXEC_MPI)
	$(MPIRUN) $(NPFLAG) $(NP) $^

# Cleaning process
clean:
	$(RM) $(EXEC_SERIAL) $(EXEC_OPENMP) $(EXEC_MPI)

