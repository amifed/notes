#include <cstring>
#include <iostream>

using namespace std;
const int N = 11;

char g[N][N];
bool row[N][N], col[N][N], cell[3][3][N];


bool dfs(int i, int j) {
    if (i >= 9) {
        for (int i = 0; i < 9; ++i) printf("%s\n", g[i]);
        return 1;
    } else if (g[i][j] != '.')
        return dfs(i + (j + 1) / 9, (j + 1) % 9);
    for (int k = 0; k < 9; ++k) {
        if (row[i][k] || col[j][k] || cell[i/3][j/3][k]) continue;
        g[i][j] = k + '1';
        row[i][k] = col[j][k] = cell[i/3][j/3][k] = 1;
        if (dfs(i + (j + 1) / 9, (j + 1) % 9)) return 1;
        g[i][j] = '.';
        row[i][k] = col[j][k] = cell[i/3][j/3][k] = 0;
    }
    return 0;
}

int main() {
    for (int i = 0; i < 9; ++i) {
        scanf("%s", g[i]);
        for (int j = 0; j < 9; ++j) {
            if (g[i][j] != '.') {
                int t = g[i][j] - '1';
                row[i][t] = col[j][t] = cell[i/3][j/3][t] = 1;
            }
        }
    }
    dfs(0, 0);
    return 0;
}