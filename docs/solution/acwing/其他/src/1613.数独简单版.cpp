#include <cstring>
#include <iostream>

using namespace std;
const int N = 11;

char g[N][N];

bool check(int r, int c, char t) {
    for (int i = 0; i < 9; ++i) {
        if (g[r][i] == t || g[i][c] == t) return 0;
        if (g[r / 3 * 3 + i / 3][c / 3 * 3 + i % 3] == t) return 0;
    }
    return 1;
}

bool dfs(int i, int j) {
    if (i >= 9) {
        return 1;
    } else if (g[i][j] != '.')
        return dfs(i + (j + 1) / 9, (j + 1) % 9);
    for (int k = '1'; k <= '9'; ++k) {
        if (!check(i, j, k)) continue;
        g[i][j] = k;
        if (dfs(i + (j + 1) / 9, (j + 1) % 9)) return 1;
        g[i][j] = '.';
    }
    return 0;
}

int main() {
    for (int i = 0; i < 9; ++i) scanf("%s", g[i]);
    dfs(0, 0);
    for (int i = 0; i < 9; ++i) printf("%s\n", g[i]);
    return 0;
}