#compile
mpicc -o output program.c

#run on P cores on 1 host
mpirun -np P ./output

#run on P cores as specified in hostfile
mpirun -np P -f hostfile ./output

