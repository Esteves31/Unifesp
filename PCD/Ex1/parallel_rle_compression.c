#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char chr;
    int count;
} RLEItem;          

/**
 * Make the RLE compression on the input.
 * @param The string that will be compressed.
 * @return The string input compressed.
*/
void compress_rle (const char *input, char *output);

int main (int argc, char *argv[]) {
    const char input[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccccccccccccccccccccccccccccccddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeffffgggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiijjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllmmmmmnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnoooooooooooooooooooooooooooooooooooooopppppppppppppppppppppppppppppppppppppqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqrrrrrrrrrrrrrrrrrrrrrrrrrrrrssssssssssssssssssssssssssssssssssttttttttttttttttttttttttttttttttttttttttttttuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    char output[100];

    clock_t start = clock();
    compress_rle(input, output);
    clock_t end = clock();
 
    const double time_spent = (double) (end - start) / CLOCKS_PER_SEC;
    printf("String comprimida: %s\n", output);
    printf("Tempo de execucao (paralela): %f segundos\n", time_spent);

    return EXIT_SUCCESS;
}

void compress_rle(const char *input, char *output) {
    int count, i, j = 0;

    #pragma omp parallel for private(i, count) 
        for (i = 0; input[i] != '\0'; i++) {
            output[j++] = input[i];
            count = 1;

            while (input[i] == input[i + 1]) {
                count++;
                i++;
            }

            j += sprintf(&output[j], "%d", count);
        }

    output[j] = '\0';

}
