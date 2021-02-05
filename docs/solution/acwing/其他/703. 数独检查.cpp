#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define fi first
#define se second
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 1e1 + 7;
const int M = 40;

int T, n;
int g[M][M];
int row[M], col[M], mat[M];

bool check(int i, int j) {
    if (row[g[i][j]] > i || col[g[j][i]] > i) return 0;
    if (mat[g[i / n * n + j / n][i % n * n + j % n]] > i) return 0;
    ++row[g[i][j]], ++col[g[j][i]], ++mat[g[i / n * n + j / n][i % n * n + j % n]];
    return 1;
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        int m = n * n;
        bool f = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &g[i][j]);
                if (g[i][j] < 1 || g[i][j] > m) f = 0;
            }
        }
        if (!f) {
            printf("Case #%d: %s\n", t, f ? "Yes" : "No");
            continue;
        }
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(mat, 0, sizeof mat);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                f &= check(i, j);
            }
        }
        printf("Case #%d: %s\n", t, f ? "Yes" : "No");
    }
    return 0;
}

/**
使用数组row, col, mat 记录行、列、矩阵中各数字出现的次数，当其超过当前行数时不满足条件；
通过遍历行 g[i][j]g[i][j] 来映射到列和矩阵是难点：
- 对于列，可以使用 g[j][i]g[j][i] 映射；
- 对于矩阵，使用 g[i/n∗n+j/n][i%n∗n+j%n]g[i/n∗n+j/n][i%n∗n+j%n] 映射；
 */