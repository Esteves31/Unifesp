#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define N_STATES 3 
#define N_TYPES_CHAR 3  // Letra, dígito e outro 

std::ifstream inputFile("sort.txt");
std::ofstream outputFile("output.txt");

const int transitionTable[N_STATES][N_TYPES_CHAR] = {{1, -1, -1}, {1, 1, 2}, {-1, -1, -1}};
const bool forwardTable[N_STATES][N_TYPES_CHAR] = {{true, false, false}, {true, true, false}, {false, false, false}};
const bool acceptTable[N_STATES] = {false, false, true};

// Retorna 0 se ch for uma letra, 1 se for dígito, e 2 se for outro tipo de caractere.
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

        int newState = transitionTable[currentState][typeChar];

        if (newState == -1) {
            if (acceptTable[currentState]) {
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

        if (forwardTable[currentState][typeChar]) {
            identifierBuffer += currentChar;
        } else {
            if (acceptTable[currentState]) {
                outputFile << "ID";
            } else {
                outputFile << identifierBuffer;
            }
            outputFile << currentChar;
            
            currentState = 0;
            identifierBuffer.clear();
        }
    }

    if (acceptTable[currentState]) {
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
