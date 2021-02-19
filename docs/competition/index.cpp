#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
using LL = long long;
const int N = 1e4 + 7, M = 2e5 + 7;

int n, m;
int h[N], e[M], ne[M], idx;

void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

int dfs(int u, int pre, int cnt) {
    if (cnt >= 4) return 1;
    int ans = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        if (v != pre) ans += dfs(v, u, cnt + 1);
    }
    return ans;
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v; 
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += dfs(i, 0, 1);
    }
    printf("%lld\n", ans);
    return 0;
}