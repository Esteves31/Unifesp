#include <stdio.h>
#include <stdbool.h>

// Função para dobrar a sequência na posição 'i'
void fold(int *S, int size_S, int i, int *result, int *size_result) {
    int left_size = i;              
    int right_size = size_S - i;    

    *size_result = (left_size > right_size) ? left_size : right_size;

    for (int j = 0; j < *size_result; j++) {
        result[j] = 0;
    }

    for (int j = 0; j < left_size; j++) {
        result[j] += S[j];
    }

    for (int j = 0; j < right_size; j++) {
        result[j] += S[size_S - 1 - j];
    }
}

// Função para verificar se D pode ser derivada de S
bool can_derive(int *S, int size_S, int *D, int size_D) {
    // Caso base: tamanho da sequência S é menor que D
    if (size_S < size_D) {
        return false;
    }

    // Verificar se D é uma subsequência de S
    for (int start = 0; start <= size_S - size_D; start++) {
        bool matches = true;
        for (int idx = 0; idx < size_D; idx++) {
            if (S[start + idx] != D[idx]) {
                matches = false;
                break;
            }
        }
        if (matches) {
            return true;
        }
    }

    // Caso base: S tem apenas 1 elemento e não é igual a D
    if (size_S == 1) {
        return false;
    }

    // Testar todas as dobras possíveis
    for (int i = 1; i < size_S; i++) {
        int result[15]; // Máximo tamanho possível para S é 15
        int size_result;

        fold(S, size_S, i, result, &size_result);

        if (can_derive(result, size_result, D, size_D)) {
            return true;
        }
    }

    return false;
}

int main() {
    int N, M;

    // Leitura do tamanho e elementos da sequência S
    scanf("%d", &N);
    int S[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    // Leitura do tamanho e elementos da sequência D
    scanf("%d", &M);
    int D[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &D[i]);
    }

    // Verificar se D pode ser derivada de S
    if (can_derive(S, N, D, M)) {
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}
