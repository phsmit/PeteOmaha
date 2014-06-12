#!/bin/bash
#SBATCH -n 1
#SBATCH -p short
#SBATCH -t 04:00:00
#SBATCH --mem-per-cpu=1000

id=$SLURM_ARRAY_TASK_ID

filename=$(ls -1 job/ | sort | sed "${id}q;d")

../build/hole_probs < job/${filename} > res/${filename}