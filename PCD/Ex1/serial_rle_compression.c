#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    printf("Tempo de execucao (sequencial): %f segundos\n", time_spent);

    return EXIT_SUCCESS;
}

void compress_rle (const char *input, char *output) {
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