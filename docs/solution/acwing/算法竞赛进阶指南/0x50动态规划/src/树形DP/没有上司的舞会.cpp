#include <iostream>
#include <cstring>
using namespace std;

const int N = 6007;

int n;
int p[N];
int h[N], e[N], ne[N], idx;
int f[N][2];
bool fa[N];

void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs(int u) {
    f[u][1] += p[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        dfs(v);
        
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        fa[u] = 1;
        add(v, u);
    }
    int root = 1;
    while (fa[root]) ++root;
    dfs(root);
    cout << max(f[root][0], f[root][1]);
    return 0;
}
