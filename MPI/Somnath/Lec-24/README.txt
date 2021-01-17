For Assignment 1
#compile using the math library
mpicc code.c -lm -o output

#run
mpirun -np 2 ./output
