# include <stdio.h>
# include <time.h>

# define N 100 // Tamanho da grade
# define T 100000 // Número de iterações
# define D 0.1 // Coeficiente de difusão
# define DELTA_T 0.01
# define DELTA_X 1.0

void diff_eq(double C[N][N], double C_new[N][N]) {
  for (int t = 0; t < T; t++) {
    for (int i = 1; i < N - 1; i++) {
      for (int j = 1; j < N - 1; j++) {
        C_new[i][j] = C[i][j] + D * DELTA_T * (
          (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / 
          (DELTA_X * DELTA_X));
      }
    }
    // Atualizar matriz para a próxima iteração
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

  clock_t start = clock();
  diff_eq(C, C_new);
  clock_t end = clock();
  double time = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Concentração final no centro: %f\n", C[N/2][N/2]);
  printf("Tempo de execução (serial): %f segundos\n", time);

  return 0;
}