#!/bin/bash
# Part 1: Characterize Sequential Overhead of parallel_sort
# Part 2: Characterize Parallelism in parallel_sort
# Part 3: Distributed Task Queue
# to give permission: chmod 755 part1-2-3.sh

#--threads: number of threads (defaults to 1)
#--particles: problem size
#--trials: number of times to repeat the computation
#--grainsize: sets the grainsize for the computation

# for debugging: g++ -DPPP_DEBUG -ggdb3 -m64 ...


# PART 1 -sequential
# echo "parallel_sort() with 1 thread and grainSizeVal of 40000000"
# ./driver-sort --particles 40000000 --trials 5 --grainsize 40000000 --threads 1;

# grainSizeVal=20000000

# while [ $grainSizeVal -ge 1 ]
# do
# 	echo "parallel_sort() with 1 thread and grainSizeVal of " $grainSizeVal
# 	./driver-sort --particles 40000000 --trials 5 --grainsize $grainSizeVal --threads 1;
# 	((grainSizeVal-=4000000))
# done


# PART 2 -parallelized with 4 threads
# echo "parallel_sort() with 4 threads and grainSizeVal2 of 40000000"
# ./driver-sort --particles 40000000 --trials 5 --grainsize 40000000 --threads 4;

# grainSizeVal2=20000000

# while [ $grainSizeVal2 -ge 1 ]
# do
# 	echo "parallel_sort() with 4 thread and grainSizeVal2 of " $grainSizeVal2
# 	./driver-sort --particles 40000000 --trials 5 --grainsize $grainSizeVal2 --threads 4;
# 	((grainSizeVal2-=4000000))
# done

echo "parallel_sort() with 4 threads and grainSizeVal2 of 20000000"
./driver-sort --particles 40000000 --trials 5 --grainsize 20000000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 10000000"
./driver-sort --particles 40000000 --trials 5 --grainsize 10000000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 5000000"
./driver-sort --particles 40000000 --trials 5 --grainsize 5000000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 1000000"
./driver-sort --particles 40000000 --trials 5 --grainsize 1000000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 500000"
./driver-sort --particles 40000000 --trials 5 --grainsize 500000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 100000"
./driver-sort --particles 40000000 --trials 5 --grainsize 100000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 50000"
./driver-sort --particles 40000000 --trials 5 --grainsize 50000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 1000"
./driver-sort --particles 40000000 --trials 5 --grainsize 1000 --threads 4;

echo "parallel_sort() with 4 threads and grainSizeVal2 of 100"
./driver-sort --particles 40000000 --trials 5 --grainsize 100 --threads 4;
# PART 3
# (use the modified taskgroup.c and run again)
# this data will be the third like to the graph, discuss if the distributed queue is always faster or not
