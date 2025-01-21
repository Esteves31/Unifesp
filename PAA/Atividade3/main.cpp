#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fold(const vector<int>& seq, int i) {
    int n = seq.size();
    vector<int> result(max(i, n - i), 0); 

    for (int j = 0; j < i; ++j) {
        result[j] += seq[j];
    }
    for (int j = i; j < n; ++j) {
        result[n - j - 1] += seq[j];
    }

    return result;
}

bool canBeDerived(const vector<int>& current, const vector<int>& target) {
    if (current == target) return true;

    if (current.size() < target.size()) return false;

    for (int i = 0; i <= current.size(); ++i) {
        vector<int> folded = fold(current, i);
        if (canBeDerived(folded, target)) {
            return true;
        }
    }

    return false;
}

int main() {
    int N, M;

    cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    cin >> M;
    vector<int> T(M);
    for (int i = 0; i < M; ++i) {
        cin >> T[i];
    }

    if (canBeDerived(S, T)) {
        cout << "S" << endl;
    } else {
        cout << "N" << endl;
    }

    return 0;
}
