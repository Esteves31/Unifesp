#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_keyword (char *token);
char* replace_keyword (char *token);
void process_line (char *line, FILE *output_file);

int main () {
    FILE *input_file;
    FILE *output_file;
    char Line[256];

    input_file = fopen("sort.txt", "r");
    output_file = fopen("saida.txt", "w");

    if (input_file == NULL) {
        printf("Arquivo de leitura inexistente!\n");
        return EXIT_FAILURE;
    }

    if (output_file == NULL) {
        printf("Arquivo de saida inexistente!\n");
        return EXIT_FAILURE;
    }

    while (fgets(Line, sizeof(Line), input_file)) {
        process_line(Line, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}

void process_line (char *line, FILE *output_file) {
    const char *delimiters = " ,;(){}[]\n\t";
    char *token;
    char buffer[256];
    int current_index = 0, j = 0;

    while (line[current_index] != '\0') {
        if (strchr(delimiters, line[current_index]) == NULL) {
            buffer[j++] = line[current_index];
        } 
        else {
            if (j > 0) {
                buffer[j] = '\0'; // Termina a string do token
                if (is_keyword(buffer)) {
                    fputs(replace_keyword(buffer), output_file);
                } else {
                    fputs(buffer, output_file);
                }
                j = 0; 
            }

            fputc(line[current_index], output_file);
        }
        current_index++;
    }
}

int is_keyword (char *token) {
    return (strcmp(token, "int") == 0 || strcmp(token, "while") == 0);
}

char* replace_keyword (char *token) {
    if (strcmp(token, "int") == 0)
        return "INT";
    else if (strcmp(token, "while") == 0)
        return "WHILE";
    
    return token;
}
