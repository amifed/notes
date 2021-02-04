# 最小生成树

最小生成树是在一个给定的无向图 $G(V,E)$ 中求一棵树 $T$，使得这棵树拥有图的所有顶点，且所有边都是来自图 $G$ 中的边，并且满足整棵树的边权最小。

## prim算法

prim算法适用于稠密图，一般使用邻接矩阵存储图。时间复杂度 $O(n^2)$。

```cpp
const int N = 507, INF = 0x3f3f3f3f;
// 邻接矩阵存储图，vt存储结点是否在生成树中，d存储其他点到当前最小生成树到距离
int n, m, g[N][N], vt[N], d[N];
int prim() {
    memset(d, 0x3f, sizeof d);
    int ans = 0;
    d[1] = 0; //设置 0 为生成树的 起始结点
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 1; v <= n; v++) { //从不在生成树的结点中 选择距离生成树最小的结点
            if (!vt[v] && (u == -1 || d[u] > d[v]))
                u = v;
        }
        if (d[u] == INF) return INF;	//图不连通
        ans += d[u];	//累加生成树的边权和
        vt[u] = 1;
        for (int v = 1; v <= n; v++) d[v] = min(d[v], g[u][v]); //更新点到生成树的最短距离，所以距离是点到点的边权最小值
    }
    return ans;
}
```

> prim算法和 Dijkstra算法思路相同，故也可使用堆优化将时间复杂度降到 $O(n\log n + m)$，但不具有实用性。

## kruskal算法

kruskal算法采用**边贪心**的策略，适用于稀疏图，只需存储全部边和权重即可，时间复杂度 $O(m\log m)$.

> 算法中需要判断是否连通，一般使用并查集。

```cpp
const int N = 2e5 + 7, INF = 0x3f3f3f3f;
int n, m, p[N]; // p为并查集的父结点数组
struct Edge {
    int u, v, w;
    bool operator<(const Edge &e)const { return w < e.w; }
} edges[N];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++) p[i] = i; //初始化并查集
    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        u = find(u), v = find(v);
        if (u != v) {
            p[u] = v;
            ans += w;
            cnt++;
        }
    }
    if (cnt < n - 1) return INF;
    else return ans;
}
```

