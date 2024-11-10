#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char chr;
    int count;
} RLEItem;   

char* generate_large_string (size_t size);
void compress_rle_parallel (const char *input, char *output);
void compress_rle_serial (const char *input, char *output);

int main() {
    size_t size = 1000000;
    char* input = generate_large_string(size);
    
    char* output_serial = (char*)malloc(size * 2 * sizeof(char));
    char* output_parallel = (char*)malloc(size * 2 * sizeof(char));
    
    // Testa versão serial
    clock_t start = clock();
    compress_rle_serial(input, output_serial);
    clock_t end = clock();
    double time_serial = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Testa versão paralela
    start = clock();
    compress_rle_parallel(input, output_parallel);
    end = clock();
    double time_parallel = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Verifica se as saídas são iguais
    printf("Resultados iguais: %s\n", 
           strcmp(output_serial, output_parallel) == 0 ? "Sim" : "Não");
    
    printf("Tempo serial: %f segundos\n", time_serial);
    printf("Tempo paralelo: %f segundos\n", time_parallel);
    printf("Speedup: %fx\n", time_serial / time_parallel);
    
    free(input);
    free(output_serial);
    free(output_parallel);
    
    return 0;
}

char* generate_large_string (size_t size) {
    char* large_string = (char*)malloc((size + 1) * sizeof(char));
    if (!large_string) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }
    
    srand(time(NULL));
    size_t i = 0;
    
    while (i < size) {
        // Escolhe um caractere aleatório entre 'a' e 'z'
        char c = 'a' + (rand() % 26);
        
        // Gera um número aleatório de repetições entre 1000 e 10000
        int repetitions = 1000 + (rand() % 9001);
        
        // Garante que não excederemos o tamanho total
        repetitions = (i + repetitions > size) ? size - i : repetitions;
        
        // Preenche a string com as repetições
        memset(large_string + i, c, repetitions);
        i += repetitions;
    }
    
    large_string[size] = '\0';
    return large_string;
}

void compress_rle_serial (const char *input, char *output) {
    int count, i = 0, j = 0;

    while (input[i] != '\0') {
        output[j++] = input[i];
        count = 1;

        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }

        j += sprintf(&output[j], "%d", count);
        i++;
    }

    output[j] = '\0';
}

void compress_rle_parallel (const char *input, char *output) {
    int len = strlen(input);
    //int num_threads = omp_get_num_procs();
    int num_threads = 1;
    // Aloca espaço para armazenar os resultados parciais de cada thread
    RLEItem **partial_results = (RLEItem**)malloc(num_threads * sizeof(RLEItem*));
    int *partial_sizes = (int*)calloc(num_threads, sizeof(int));
    
    for(int i = 0; i < num_threads; i++) {
        partial_results[i] = (RLEItem*)malloc(len * sizeof(RLEItem));
    }
    
    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num(); 
        int chunk_size = len / num_threads;
        int start = tid * chunk_size;
        int end = (tid == num_threads - 1) ? len : (tid + 1) * chunk_size;
        
        if (tid > 0) {
            while (start > 0 && input[start] == input[start - 1]) {
                start--;
            }
        }
        
        if (tid < num_threads - 1) {
            while (end < len && input[end] == input[end - 1]) {
                end++;
            }
        }
        
        int local_index = 0;
        for (int i = start; i < end; i++) {
            char current = input[i];
            int count = 1;
            
            while (i + 1 < end && input[i] == input[i + 1]) {
                count++;
                i++;
            }
            
            partial_results[tid][local_index].chr = current;
            partial_results[tid][local_index].count = count;
            local_index++;
        }
        partial_sizes[tid] = local_index;
    }
    
    int output_index = 0;
    char last_char = '\0';

    for (int t = 0; t < num_threads; t++) {
        for (int i = 0; i < partial_sizes[t]; i++) {
            char current_char = partial_results[t][i].chr;
            
            if (output_index > 0 && current_char == last_char) {
                continue;
            }
            
            output[output_index++] = current_char;
            output_index += sprintf(&output[output_index], "%d", 
                                partial_results[t][i].count);
            last_char = current_char;
        }
    }
    output[output_index] = '\0';
    
    // Libera a memória
    for(int i = 0; i < num_threads; i++) {
        free(partial_results[i]);
    }
    free(partial_results);
    free(partial_sizes);
}