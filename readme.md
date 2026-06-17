## Install mpi
sudo apt install mpich

## Compile and run
mpicc -o ./bin/program_name file_name.c
mpirun -np 4 ./bin/program_name