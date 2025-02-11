#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void indexTo2D(int index, int n, int& row, int& col) {
    row = index / n;
    col = index % n;
}

bool isValid(const vector<int>& queens, int n) {
    vector<bool> rows(n, false);
    vector<bool> cols(n, false);
    for (int i=0; i<n; i++) {
        int r, c;
        indexTo2D(queens[i], n, r, c);
        if (rows[r] || cols[c]) return false;
        rows[r] = true;
        cols[c] = true;
    }

    for (int i = 0; i<n; i++) {
        int r1, c1;
        indexTo2D(queens[i], n, r1, c1);
        for (int j = i + 1; j<n; j++) {
            int r2, c2;
            indexTo2D(queens[j], n, r2, c2);
            if (abs(r1 - r2) == abs(c1 - c2)) return false;
        }
    }
    return true;
}


void generateCombinations(int start, int n, int remaining, vector<int>& current, vector<vector<int>>& valid) {
    if (remaining == 0) {
        if (isValid(current, n)) {
            valid.push_back(current);
        }
        return;
    }

    for (int i = start; i < n * n; i++) {
        current.push_back(i);
        generateCombinations(i + 1, n, remaining - 1, current, valid);
        current.pop_back();
    }
}

int main(){
    int n;
    cin >> n;

    vector<vector<int>> valid_queens;
    vector<int> current;
    generateCombinations(0, n, n, current, valid_queens);

    for (const auto& queens : valid_queens) {
        vector<string> board(n, string(n, 'o'));
        for (int pos : queens) {
            int r, c;
            indexTo2D(pos, n, r, c);
            board[r][c] = 'Q';
        }
        for (const string& row : board) {
            cout << row << endl;
        }
        cout << endl;
    }
    return 0;
}