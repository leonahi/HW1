# Build process for MPI using OpenMPI
#
# Author: Nahit Pawar
#         M.Tech - Electrical Dept. - IITB
# 
# Date: 06-Feb-2014 

MPI=mpic++
MPIRUN=mpirun

NP=4
NPFLAG=-np

PROJ=main.cpp
OBJECTS=main.o
EXEC=exec

RM=rm

.PHONY: all
.PHONY: clean
.PHONY: compile
.PHONY: run
.PHONY: acknowledge

all: $(OBJECTS) compile acknowledge

# Object file creation
$(OBJECTS): $(PROJ)
	$(MPI) -o $@ -c $^

# Compilation Process
compile: $(EXEC)

$(EXEC): $(OBJECTS)
	$(MPI) -o $@ $^

# Run process
run: $(EXEC)
	$(MPIRUN) $(NPFLAG) $(NP) $^

# Cleaning process
clean:
	$(RM) $(OBJECTS) $(EXEC)

acknowledge:
	@echo " "
	@echo "Compilation Done Successfully"
	@echo " "


