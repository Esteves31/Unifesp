#include <stdio.h>
#include <stdlib.h>

int minCaixas(int tamCaixas[], int qtdCaixas, int qtdProdutos);

int main() {
    int qtdProdutos, qtdCaixas;
    scanf("%d %d", &qtdProdutos, &qtdCaixas);

    int tamCaixas[qtdCaixas];
    for (int i = 0; i < qtdCaixas; i++) {
        scanf("%d", &tamCaixas[i]);
    }

    int resultado = minCaixas(tamCaixas, qtdCaixas, qtdProdutos);
    printf("%d\n", resultado);

    return EXIT_SUCCESS;
}

int minCaixas(int tamCaixas[], int qtdCaixas, int qtdProdutos) {
    int dp[qtdProdutos + 1];

    for (int i = 0; i <= qtdProdutos; i++) {
        dp[i] = 1e9;
    }

    dp[0] = 0;

    for (int i = 1; i <= qtdProdutos; i++) {
        for (int j = 0; j < qtdCaixas; j++) {
            if (tamCaixas[j] <= i && dp[i - tamCaixas[j]] != 1e9) {
                dp[i] = (dp[i] < dp[i - tamCaixas[j]] + 1) ? dp[i] : dp[i - tamCaixas[j]] + 1;
            }
        }
    }

    return dp[qtdProdutos];
}