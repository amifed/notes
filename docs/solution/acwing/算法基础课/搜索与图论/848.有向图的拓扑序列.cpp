#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 1e5 + 7;
int n, m;
int h[N], e[N], ne[N], idx;
int ind[N];

void add(int u, int v) { e[idx] = v, ne[idx] = h[u], h[u] = idx++; }

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (!ind[i]) q.push(i);

    while (!q.empty()) {
        auto t = q.front();
        printf("%d ", t);
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int u = e[i];
            --ind[u];
            if (!ind[u]) q.push(u);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        ++ind[b];
    }
    topsort();
    return 0;
}