#include <cstring>
#include <iostream>
using namespace std;

const int N = 10;
int n;
char q[N][N];
int vt[N];

// bool check(int u, int v) {
//     for (int i = 0; i < u; ++i) {
//         if (vt[i] == v || vt[i] + i == u + v || vt[i] - i == v - u) return 0;
//     }
//     return 1;
// }
// void dfs(int u) {
//     if (u == n) {
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j)
//                 printf("%c", q[i][j]);
//             printf("\n");
//         }
//         printf("\n");
//         return;
//     }
//     for (int i = 0; i < n; ++i) {
//         if (check(u, i)) {
//             q[u][i] = 'Q';
//             vt[u] = i;
//             dfs(u + 1);
//             q[u][i] = '.';
//         }
//     }
// }

bool check(int u, int v) {
    if (vt[u] != -1) return 0;
    for (int i = 0; i < u; ++i) {
        if (vt[i] == v || vt[i] + i == u + v || vt[i] - i == v - u) return 0;
    }
    return 1;
}
void dfs(int x, int y, int u) {
    if (y == n) x++, y = 0;
    if (x == n) {
        if (u == n) {
            for (int i = 0; i < n; ++i)
                puts(q[i]);
            puts("");
        }
        return;
    }

    // 不放皇后
    dfs(x, y + 1, u);

    // 放皇后
    if (check(x, y)) {
        q[x][y] = 'Q';
        vt[x] = y;
        dfs(x, y + 1, u + 1);
        q[x][y] = '.';
        vt[x] = -1;
    }
}

int main() {
    scanf("%d", &n);
    memset(vt, -1, sizeof vt);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            q[i][j] = '.';
    dfs(0, 0, 0);
    return 0;
}