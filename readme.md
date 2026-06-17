## Install mpi
sudo apt install mpich

## Compile
- mpicc -o ./bin/program_name file_name.c

## Run
- mpirun -np 4 ./bin/program_name