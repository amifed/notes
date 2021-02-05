#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 507, M = 1e5 + 7, INF = 0x3f3f3f3f;
int g[N][N], d[N], vt[N];
int n, m;
void dijkstra() {
    memset(d, 0x3f, sizeof d);
    memset(vt, 0, sizeof vt);
    d[1] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!vt[j] && (u != -1 || d[j] < d[u])) u = j;
        }
        vt[u] = 1;
        for (int v = 1; v <= n; v++) {
            d[v] = min(d[v], d[u] + g[u][v]);
        }
    }
}
int main() {
    memset(g, 0x3f, sizeof g);
    scanf("%d%d", &n, &m);
    int x, y, z;
    while (m--) {
        scanf("%d%d%d", &x, &y, &z);
        g[x][y] = min(g[x][y], z);
    }
    dijkstra();
    if (d[n] == INF)
        puts("-1");
    else
        printf("%d\n", d[n]);
    return 0;
}