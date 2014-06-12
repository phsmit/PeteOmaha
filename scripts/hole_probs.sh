#!/bin/bash


rm -Rf job res
mkdir -p job 
mkdir -p res

../build/unique_holes > uniques
split -l 20 uniques job/job

num_jobs=$(ls -1 job | wc -l)

sbatch --array=0-${num_jobs} hole_probs_job.sh