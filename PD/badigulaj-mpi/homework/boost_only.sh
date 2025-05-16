#!/bin/bash

#SBATCH --ntasks-per-node=2 # Кол-во задач на процессор/машину
#SBATCH --job-name=PD-AitoreTask # Имя задачи для очереди
#SBATCH --comment="Run student mpi from config" # Крайне обязательный пункт, без него придёт автокил
#SBATCH --output=boost_only.txt # Файл для печати вывода 
#SBATCH --error=error_boost_only.txt # Файл для печати ошибок
sbcast -f boost_only boost_only
mpiexec ./boost_only 100000000.0