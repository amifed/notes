#include <cstring>
#include <iostream>
using namespace std;

const int N = 10;
int g[N][N];
int n, vt[2][N]; // 0 黑 1 白
// int ans;

bool check(int vt[], int x, int y) {
    for (int i = 0; i < x; ++i) {
        if (vt[i] == y || x + y == vt[i] + i || x - y == i - vt[i]) return 0;
    }
    return 1;
}

int dfs(int r, int k) {
    if (r == n) return 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (check(vt[k], r, i) && g[r][i]) {
            vt[k][r] = i, g[r][i] = 0;
            ans += dfs(r + k, k ^ 1);
            vt[k][r] = -1, g[r][i] = 1;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &g[i][j]);
    cout << dfs(0, 0);
    return 0;
}