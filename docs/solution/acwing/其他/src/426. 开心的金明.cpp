#include <algorithm>
#include <iostream>

using namespace std;

const int N = 3e4 + 7, M = 30;
int n, m;
int f[M][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int v, p;
        cin >> v >> p;
        int w = v * p;
        for (int j = 0; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w);
        }
    }
    cout << f[m][n];
    return 0;
}
/*
01背包
*/