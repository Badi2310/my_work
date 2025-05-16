#!/bin/bash

#SBATCH --ntasks-per-node=2 # Кол-во задач на процессор/машину
#SBATCH --job-name=PD-AitoreTask # Имя задачи для очереди
#SBATCH --comment="Run student mpi from config" # Крайне обязательный пункт, без него придёт автокил
#SBATCH --output=main.txt # Файл для печати вывода 
#SBATCH --error=error_main.txt # Файл для печати ошибок
sbcast -f main main
mpiexec ./main 1000