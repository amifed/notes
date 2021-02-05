#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 507, INF = 0x3f3f3f3f;
// 邻接矩阵存储图，vt存储结点是否在生成树中，d存储其他点到当前最小生成树到距离
int n, m, g[N][N], vt[N], d[N];

int prim() {
    memset(d, 0x3f, sizeof d);
    int ans = 0;
    d[1] = 0; //设置 0 为生成树的 起始结点
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (!vt[v] && (u == -1 || d[u] > d[v]))
                u = v;
        }
        if (d[u] == INF) return INF;
        ans += d[u];
        vt[u] = 1;
        for (int v = 1; v <= n; v++) d[v] = min(d[v], g[u][v]);
    }
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    memset(g, 0x3f, sizeof g);
    while (m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    int ans = prim();
    if (ans == INF) printf("impossible");
    else printf("%d", ans);
    return 0;    
}