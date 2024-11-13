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
        
        if (typeChar != 0)
            error = true;

        while (!accept[currentState] && !error) {
            typeChar = charType(currentChar);
            int newState = T[currentState][typeChar];

            if (newState == -1) {
                error = true;
                break;
            }

            if (forward[currentState][typeChar]) {
                char nxt = inputFile.peek();

                if (charType(nxt) != 2) 
                    inputFile.get(currentChar);
            } 

            currentState = newState;
        }

        if (accept[currentState]) {
            outputFile << "ID";
        }
        else {
            outputFile << currentChar;
        }

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