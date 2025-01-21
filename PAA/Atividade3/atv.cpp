#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

// Função que realiza uma dobra na posição 'i' da sequência original
vector<int> dobra(const vector<int>& seq, int i) {
    int n = seq.size();
    vector<int> result;

    // Parte esquerda da sequência original (antes de 'i')
    for (int j = 0; j < i; j++) {
        result.push_back(seq[j]);
    }

    // Parte direita invertida e somada na esquerda
    for (int j = 0; j < n - i; j++) {
        if (i - j - 1 >= 0) { // Sobreposição
            result[i - j - 1] += seq[n - 1 - j];
        } else { // Sem sobreposição (elementos adicionais)
            result.push_back(seq[n - 1 - j]);
        }
    }

    return result;
}

// Função para gerar uma chave única da sequência (para memoização)
string gerarChave(const vector<int>& seq) {
    string chave = "";
    for (int x : seq) {
        chave += to_string(x) + ",";
    }
    return chave;
}

// Função recursiva para verificar se T é derivada de S, com memoização
bool ehDerivada(const vector<int>& S, const vector<int>& T, unordered_set<string>& memo) {
    if (S == T) return true; // Se S == T, é derivada
    if (S.size() < T.size()) return false; // T não pode ser maior que S

    // Gerar chave única para o estado atual
    string chave = gerarChave(S);

    // Verificar se já processamos esta sequência
    if (memo.count(chave)) return false;
    memo.insert(chave);

    // Tentar dobrar em todas as posições
    for (int i = 0; i <= S.size(); i++) {
        vector<int> novaSeq = dobra(S, i);
        if (i == 3)
            for (int idx = 0; idx < novaSeq.size(); idx++) {
                cout << novaSeq[idx] << ", ";
            }
        cout << '\n';
        if (ehDerivada(novaSeq, T, memo)) {
            return true;
        }
    }

    return false;
}

int main() {
    int N, M;

    // Leitura da entrada
    cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    cin >> M;
    vector<int> T(M);
    for (int i = 0; i < M; i++) {
        cin >> T[i];
    }

    // Estrutura para armazenar estados visitados
    unordered_set<string> memo;

    // Verificação e saída
    if (ehDerivada(S, T, memo)) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
