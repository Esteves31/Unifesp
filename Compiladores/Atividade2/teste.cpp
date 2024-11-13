#include <cctype>
#include <fstream>
#include <iostream>

#define N_STATES 3
#define N_TYPES_CHAR 3

std::ifstream inputFile("sort.txt");
std::ofstream outputFile("output.txt");

int T[N_STATES][N_TYPES_CHAR] = {   {1, -1, -1},
                                    {1, 1, 2},
                                    {-1, -1, -1}   };

bool forward[N_STATES][N_TYPES_CHAR] {  {true, false, false},
                                        {true, true, false},
                                        {false, false, false}   };

bool accept[N_STATES] = {false, false, true};

// Return 0 if ch is a char, 1 if ch is a integer and 2 if ch is other character.
int charType(char ch);

int main() {
    bool error = false;
    char currentChar;
    int currentState = 0;
    int typeChar;

    if (!outputFile.is_open() || !inputFile.is_open()) {
        std::cout << "Could not open the files";
        return -1;
    }

    while (inputFile.get(currentChar)) {
        typeChar = charType(currentChar);

        // Handle non-identifier characters directly
        if (typeChar != 0) {
            outputFile << currentChar;
            currentState = 0; // Reinicia o estado para o próximo identificador
            continue;
        }

        while (!accept[currentState] && !error) {
            int newState = T[currentState][typeChar];

            // Verifica se a transição é válida
            if (newState == -1) {
                error = true;
                std::cerr << "Erro: Transição inválida!" << std::endl;
                break; // Sai do loop interno e trata o erro
            }

            // Consome o caractere se necessário
            if (forward[currentState][typeChar]) {
                inputFile.get(currentChar);
            }

            currentState = newState;
        }

        // Processa o estado final
        if (accept[currentState]) {
            outputFile << "ID";
        } else if (error) {
            // Trata o erro
            std::cerr << "Erro: Palavra inválida" << std::endl;
        } else {
            // Caractere não pertence a um identificador válido
            outputFile << currentChar;
        }

        // Reinicia o estado para o próximo identificador
        currentState = 0;
        error = false;
    }

    return 0;
}

int charType(char ch) {
    if (isalpha(ch)) return 0;
    if (isdigit(ch)) return 1;
    return 2;
}