Assignment #2 - Implementing Parallel Task Library

Assignment & Unmodified Code Available at : https://www.cis.upenn.edu/~cis534/ppp3.html


To compile:

g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 ppp.C random.C TaskGroup.C driver-sort.C -o driver-sort
g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 ppp.C random.C TaskGroup.C driver-compute.C -o driver-compute
g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 ppp.C random.C TaskGroup.C driver-reduce.C -o driver-reduce


Command Line Parameters:
--threads: number of threads (defaults to 1)
--particles: problem size
--trials: number of times to repeat the computation
--grainsize: sets the grainsize for the computation


Examples of tests given by professor:

./driver-sort --particles 40000000 --trials 5 --grainsize 1000 --threads 4
./driver-compute --particles 10000000 --trials 5 --grainsize 1000 --threads 4
./driver-reduce --particles 100000000 --trials 5 --grainsize 1000 --threads 4


The 3 files that we modified are:

-TaskGroup.C
-parallel_for.h
-parallel_reduce.h