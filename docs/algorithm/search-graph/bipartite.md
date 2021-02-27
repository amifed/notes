# 二分图

## 染色法判断二分图

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 7, M = 2e5 + 7;

int n, m;
int h[N], e[M], ne[M], idx;
int color[N];
void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

bool dfs(int u, int c) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        if (!color[v]) {
            if (!dfs(v, 3 - c)) return 0;
        } else if (color[v] == c) return 0;
    }
    return 1;
}

bool isBipartite() {
    for (int i = 1; i <= n; ++i) {
        if (!color[i]) {
            if (!dfs(i, 1)) return 0;
        }
    }
    return 1;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    if (isBipartite()) cout << "Yes";
    else cout << "No";
    return 0;
}
```