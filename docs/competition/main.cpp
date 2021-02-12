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
const int M = 2e4 + 7;

int n, m;
int p[N][N];
int can[N];
int tk[N], vt[N];
int cnt, ans[M][N];

bool check() {
    for (int i = 0; i < m; ++i) {
        int k = 1;
        for (int j = 0; j < n && k <= p[i][0]; ++j) {
            if (tk[j] == p[i][k]) ++k;
        }
        if (k == p[i][0] + 1 && !can[i])
            return 0; // 第 i 个预测序列错误，但相对序列对得上
        if (k != p[i][0] + 1 && can[i])
            return 0; // 第 i 个预测序列正确，但相对序列对不上
    }
    return 1;
}

void dfs(int idx) {
    if (idx == n) {
        if (check()) {
            memcpy(ans[cnt++], tk, sizeof tk);
        }
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!vt[i]) {
            vt[i] = 1, tk[idx] = i;
            dfs(idx + 1);
            vt[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%d", &p[i][0]);
        for (int j = 1; j <= p[i][0]; ++j)
            scanf("%d", &p[i][j]);
        scanf("%d", &can[i]);
    }

    dfs(0);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", ans[i][j]);
        }
        puts("");
    }
    return 0;
}