# include <stdio.h>
# include <omp.h>

# define N 100 // Tamanho da grade
# define T 100000 // Número de iterações
# define D 0.1 // Coeficiente de difusão
# define DELTA_T 0.01
# define DELTA_X 1.0

void diff_eq(double C[N][N], double C_new[N][N]) {
  for (int t = 0; t < T; t++) {
    #pragma omp parallel for collapse(2)    
    for (int i = 1; i < N - 1; i++) {
      for (int j = 1; j < N - 1; j++) {
        C_new[i][j] = C[i][j] + D * DELTA_T * (
          (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / 
          (DELTA_X * DELTA_X));
      }
    }
    
    #pragma omp parallel for collapse(2)
    for (int i = 1; i < N - 1; i++) {
      for (int j = 1; j < N - 1; j++) {
        C[i][j] = C_new[i][j];
      }
    }
  }
}

int main() {
  double C[N][N] = {0}; // Concentração inicial
  double C_new[N][N] = {0}; // Concentração para a próxima iteração
  
  // Inicializar uma concentração alta no centro
  C[N/2][N/2] = 1.0;

  omp_set_num_threads(4);

  double start = omp_get_wtime();
  diff_eq(C, C_new);
  double end = omp_get_wtime();
  double time = end - start;

  printf("Concentração final no centro: %f\n", C[N/2][N/2]);
  printf("Tempo de execução (serial): %f segundos\n", time);

  return 0;
}