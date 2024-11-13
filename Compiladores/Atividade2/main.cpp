#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define N_STATES 3
#define N_TYPES_CHAR 3

std::ifstream inputFile("sort.txt");
std::ofstream outputFile("output.txt");

int T[N_STATES][N_TYPES_CHAR] = {   {1, -1, -1},
                                    {1, 1, 2},
                                    {-1, -1, -1}   };

bool forward[N_STATES][N_TYPES_CHAR] = { {true, false, false},
                                         {true, true, false},
                                         {false, false, false} };

bool accept[N_STATES] = {false, false, true};

// Retorna 0 para letras, 1 para dígitos, e 2 para outros caracteres.
int charType(char ch);

int main() {
    char currentChar;
    int currentState = 0;
    bool error = false;
    std::string identifierBuffer;

    if (!outputFile.is_open() || !inputFile.is_open()) {
        std::cout << "Could not open the files";
        return -1;
    }

    while (inputFile.get(currentChar)) {
        int typeChar = charType(currentChar);

        int newState = T[currentState][typeChar];

        if (newState == -1) {
            if (accept[currentState]) {
                outputFile << "ID";
            } else {
                outputFile << identifierBuffer;
            }
            outputFile << currentChar;

            currentState = 0;
            identifierBuffer.clear();
            error = false;
            continue;
        }

        currentState = newState;

        if (forward[currentState][typeChar]) {
            identifierBuffer += currentChar;
        } else {
            if (accept[currentState]) {
                outputFile << "ID";
            } else {
                outputFile << identifierBuffer;
            }
            outputFile << currentChar;
            
            currentState = 0;
            identifierBuffer.clear();
        }
    }

    if (accept[currentState]) {
        outputFile << "ID";
    } else {
        outputFile << identifierBuffer;
    }

    inputFile.close();
    outputFile.close();
    
    return 0;
}

int charType(char ch) {
    if (isalpha(ch)) return 0;
    if (isdigit(ch)) return 1;
    return 2;
}
