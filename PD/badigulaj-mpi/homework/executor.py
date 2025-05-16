import subprocess as sp
import time as tm
import matplotlib.pyplot as plt

def Update(segments): # меняет N
  with open("boost_only.sh", "r") as file:
    line_array = file.readlines()
    line_array = line_array[:-1]
  
  last_line = f"mpiexec ./boost_only {segments}"

  with open("boost_only.sh", "w") as file:
    line_array.append(last_line)
    file.writelines(line_array)

def get_boost(): # получает S из boost_only.txt
  with open("boost_only.txt", "r") as file:
    boost_val = float(file.read())
    return boost_val



N_array = [1000, 1e6, 1e8]


for ind, N in enumerate(N_array):
  Update(N)
  S_array = []
  for i in range(1, 9):
    tm.sleep(30)
    sp.Popen(f"sbatch --ntasks={i} boost_only.sh", shell=True)
    S_i = get_boost()
    S_array.append(S_i)

  plt.plot(range(1, 9), S_array, label = f"N = {N}")
plt.legend()
plt.savefig("images.pdf")