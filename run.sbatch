#!/bin/bash -l
#SBATCH --account=proj16
#SBATCH -t 20:00:00 
#SBATCH --exclusive
#SBATCH --hint=compute_bound

module purge

module load intel-parallel-studio
omp_threads=(1 2 4 8 16 18)

for nthreads in "${omp_threads[@]}"
do
  echo "Running with $nthreads threads"
  export OMP_NUM_THREADS=$nthreads
  echo "thread, mem, bpc, gbps, chk"  >> cbench_$nthreads.log
  numactl -N 0 ./cbench >> cbench_$nthreads.log
done
