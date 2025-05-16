#include <mpi.h>
#include <iostream>

double f(double x) {
  return 4 / (1 + x * x);
}

double count(int rank, int N, int iter) {
  double result = 0;
  for (int i = rank; i < N; i += iter) {
    double x = i;
    x /= N;

    double delta = 1;
    delta /= N;

    result += (f(x) + f(x + delta)) * delta / 2;
  }
  return result;
}

int main(int argc, char** argv){
  double S = 0;
  double S_0 = 0;
  int N;
  N = strtol(argv[1], NULL, 10);

  MPI_Init(&argc, &argv);

  int world_size;
  int world_rank;

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Status status;

  double I_i = 0;
  double start = MPI_Wtime();
  I_i = count(world_rank, N, world_size);
  std::cout << world_rank << " посчитал "<< I_i << '\n';

  if (world_rank != 0) {
    MPI_Send(
      &I_i,
      1,
      MPI_DOUBLE,
      0, //receiver
      0, 
      MPI_COMM_WORLD
    );
  } else {
    S += I_i;
    for (int i = 1; i < world_size; ++i) {
      MPI_Recv(
        &I_i,
        1,
        MPI_DOUBLE,
        i, //sender
        0,
        MPI_COMM_WORLD,
        &status
      );
      S += I_i;
    }

    double end = MPI_Wtime();

    double start0 = MPI_Wtime();
    S_0 = count(0, N, 1);
    double end0 = MPI_Wtime();

    std::cout << "несколько процессов: " << S << '\n';
    std::cout << "основной процесс: " << S_0 << '\n';
  }

  MPI_Finalize();
    
  return 0;
}