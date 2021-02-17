# 单源最短路径

## Dijkstra

算法思想：
对图 $G(V,E)$  设置集合 $S$，存放已被访问的结点，然后每次从集合 $V - S$ 中选择与起点 $s$ 的距离最小的一个结点（记为 $u$ ），访问并加入集合 $S$ 。之后，令结点 $u$ 为中介点，优化结点 $u$ 能到达的结点 $v$ 之间的最短距离。重复这样的操作 $n$ 次。

### 邻接矩阵

适用于稠密图，时间复杂度 $O(n^2)$

```cpp
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 507;
const int M = 1e5 + 7;
int g[N][N];
int n, m, d[N], vt[N];
void dijkstra(int s) {
    memset(vt, 0, sizeof vt);
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int u, minn = INF; //寻找当前未访问的最小节点
        for (int j = 1; j <= n; j++) {
            if (!vt[j] && d[j] < minn) {
                u = j, minn = d[j];
            }
        }
        vt[u] = 1; // u为中介点，优化结点 u 能到达的结点 v 之间的最短距离
        for (int v = 1; v <= n; v++) {
            d[v] = min(d[v], d[u] + g[u][v]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(g, 0x3f, sizeof g);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        g[u][v] = min(g[u][v], w); //防止重边
    }
    dijkstra(1);
    printf("%d\n", d[n] == INF ? -1 : d[n]);
    return 0;
}
```



### 邻接表

适用于稀疏图，时间复杂度$O(n^2)$

```cpp
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 507;
const int M = 1e5 + 7;
int h[N], w[M], e[M], ne[M], idx;
int n, m, d[N], vt[N];
void add(int u, int v, int x) {
    e[idx] = v, w[idx] = x, ne[idx] = h[u], h[u] = idx++;
}
void dijkstra(int s) {
    memset(vt, 0, sizeof vt);
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int u, minn = INF;
        for (int j = 1; j <= n; j++) {
            if (!vt[j] && d[j] < minn) {
                u = j, minn = d[j];
            }
        }
        vt[u] = 1;
        for (int j = h[u]; j != -1; j = ne[j]) {
            int v = e[j];
            d[v] = min(d[v], d[u] + w[j]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    idx = 0;
    memset(h, -1, sizeof h);
    int u, v, x;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &x);
        add(u, v, x);
    }
    dijkstra(1);
    printf("%d\n", d[n] == INF ? -1 : d[n]);
    return 0;
}
```

### 邻接表 + 堆优化

用堆维护起点到所有点的距离，时间复杂度$O(m\log n)$

```cpp
void dijkstra(int s) {
    memset(vt, 0, sizeof vt);
    memset(d, 0x3f, sizeof d);
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<PII>> pq; //最小堆
    d[s] = 0;
    pq.push({0, s}); //将 起点入队，{距离，结点编号}
    while (!pq.empty()) {
        auto t = pq.top(); //起点出发到达的距离最短结点
        pq.pop();
        int u = t.second, dist = t.first;
        if (vt[u]) continue; //之前更新过，冗余
        vt[u] = 1;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (d[v] > w[i] + dist) { // u为中介点，优化结点 u 能到达的结点 v 之间的最短距离
                d[v] = w[i] + dist;
                pq.push({d[v], v});
            }
        }
    }
}
```

### 最短路径记录

定义 `pre` 记录前驱结点，最后 dfs 回溯；

- 一条路径

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
using PII = pair<int, int>;
const int INF = 0x3f3f3f3f;
const int N = 501;
const int M = 1e5 + 7;
int h[N], e[M], w[M], ne[M], idx;
int d[N], vt[N] = {0}, pre[N];
int n, m, st, ed;
void add(int x, int y, int z) {
    e[idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx++;
}
void dijkstra(int s) {
    memset(d, 0x3f, sizeof d);
    memset(c, 0x3f, sizeof c);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    d[s] = c[s] = 0;
    pre[s] = s;
    pq.push({0, s});
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int u = t.second, dist = t.first;
        if (vt[u]) continue;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (d[v] > w[i] + dist) {
                d[v] = w[i] + dist;
                pq.push({d[v], v});
                pre[v] = u;
            }
        }
    }
}
void dfs(int v) { //递归输出有起点到终点的路径
    if (v == pre[v]) {
        printf("%d ", v);
        return;
    }
    dfs(pre[v]);
    printf("%d ", v);
}
int main() {
    scanf("%d %d %d %d", &n, &m, &st, &ed);
    idx = 0;
    memset(h, -1, sizeof h);
    int u, v, x, y;
    forr(i, 0, m) {
        scanf("%d %d %d %d", &u, &v, &x, &y);
        add(u, v, x);
        add(v, u, x);
        cst[u][v] = y;
        cst[v][u] = y;
    }
    dijkstra(st);
    dfs(ed);
    return 0;
}
```

- 多条路径

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
using PII = pair<int, int>;
const int INF = 0x3f3f3f3f;
const int N = 501;
const int M = 1e5 + 7;

int h[N], e[M], w[M], ne[M], idx;
int d[N], vt[N] = {0};
int n, m, st, ed;
void add(int x, int y, int z) {
    e[idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx++;
}
void dijkstra(int s) {
    memset(d, 0x3f, sizeof d);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    d[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int u = t.second, dist = t.first;
        if (vt[u]) continue;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (d[v] > w[i] + dist) {
                d[v] = w[i] + dist;
                pq.push({d[v], v});
                pre[v].clear(); //存在最优解清空
                pre[v].pub(u);
            } else if (d[v] == w[i] + dist) {
                pre[v].pub(u); //相同最优加入
            }
        }
    }
}
vector<int> path;
void dfs(int v) {
    if (v == st) {
        path.pub(v);
        for (int i = path.size() - 1; i > 0; i--) {
            printf("%d ", path[i]);
        }
        path.pob();
        return;
    }
    path.pub(v);
    for (auto &x : pre[v])
        dfs(x);
    path.pob();
}
int main() {
    scanf("%d %d %d %d", &n, &m, &st, &ed);
    idx = 0;
    memset(h, -1, sizeof h);
    int u, v, x, y;
    forr(i, 0, m) {
        scanf("%d %d %d %d", &u, &v, &x, &y);
        add(u, v, x);
        add(v, u, x);
        cst[u][v] = y;
        cst[v][u] = y;
    }
    dijkstra(st);
    dfs(ed);
    return 0;
}
```

## Bellman-Ford

用于求解有负权边的最短路径问题。

**算法思想**：对图中对边做 $V - 1$ 轮松弛操作，每轮都遍历所有的边，对每条边 `u -> v`，如果以 `u`为中介点可以使 `d[v]` 更小，即 $d[v] + w[u -> v] < d[v]$ 成立时，就更新 `d[v]`。若途中不存在源点可达的负权环时， $V - 1$ 次松弛操作后 `d` 中的值都是最优的；若存在源点可达的负权环时，第 $V$ 次松弛操作仍存在更新，且如果一直松弛下去负权环上的 `d` 将会趋于 $-\infty$。

时间复杂度 $O(VE)$

```cpp
const int INF = 0x3f3f3f3f;
const int N = 1e5 + 7;
const int M = 1e5 + 7;
int n, m;
int d[N];
struct Edge {
    int u, v, w;
} edges[M];
// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
int bellman_ford(int s) {
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    // 如果第n次迭代仍然会松弛，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
            }
        }
    }
    if (d[n] > INF / 2) return -1;
    return d[n];
}
```

## SPFA

SPFA (Shortest Path Faster Algorithm)，是队列优化的 Bellman-Ford 算法，时间复杂度 平均情况下 $O(E)$ ，最坏情况即存在源点可达的负环时，时间复杂度退化为 $O(nm)$ 。

Bellman-Ford 算法中每轮都会遍历所有的边，其中会有一些无意义的操作。其中，只有当某个顶点 `u` 的 `d[u]` 改变时， 从它出发的边的邻接点 `v` 才有可能改变。因此可以使用一个队列优化。

**算法思想**：

1. 建立一个队列，首先将源点放入队列。
2. 将队首顶点 $u$ 取出，然后对 $u$ 出发的所有边 `u -> v` 进行松弛操作，即判断 `d[u] + w[v] < d[v]` 是否成立，如果成立，则更新 `d[v]`，此时如果 $v$ 如果不在队列中，就把 $v$ 入队。
3. 重复步骤 2 直到队列为空（说明图中没有从源点可达的负环），或是某个顶点的入队次数超过 $V - 1$ （说明图中存在从源点可达的负环）。

**参考代码**

- 源点 s 到图中各点的最短距离

```cpp
int spfa(int s) {
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    vt[s] = 1;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vt[u] = 0;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (d[v] > d[u] + w[i]) {
                d[v] = d[u] + w[i];
                if (!vt[v]) {
                    q.push(v);
                    vt[v] = 1;
                }
            }
        }
    }
}
```

- 判断图中是否存在负环

  - 根据入队次数

  使用数组 `cnt[x]` 记录结点入队次数，如果某个入队次数超过 $V - 1$ 次，则图中存在源点可达的负环。这个方法来判断相对来说是有些慢的，因为如果一个由 n 个结点构成的负环需要绕 n 次，才能使负环上的点入队 n 次；

  ```cpp
  int spfa(int s) {
      memset(d, 0x3f, sizeof d);
      memset(cnt, 0, sizeof cnt);
      d[s] = 0;
      queue<int> q;
      q.push(s);
      vt[s] = 1;
      cnt[s]++;
      while (!q.empty()) {
          auto u = q.front();
          q.pop();
          vt[u] = 0;
          for (int i = h[u]; i != -1; i = ne[i]) {
              int v = e[i];
              if (d[v] > d[u] + w[i]) {
                  d[v] = d[u] + w[i];
                  if (!vt[v]) {
                      q.push(v);
                      vt[v] = 1;
                      cnt[v]++;
                      if (cnt[v] >= n) return true; ；//入队超过 n 次
                  }
              }
          }
      }
      return false;
  }
  ```

  - 根据点的个数

  对于一个不存在负环的图，从起点到任意一个点最短距离经过的点最多只有 n 个。如果某条最短路径上有 n 个点（除了自己），那么加上自己之后一共有 n+1 个点，由抽屉原理一定有两个点相同，所以存在环。使用 `cnt[u]` 来记录从源点到点 $u$ 最短距离中的结点个数，初始化为 $0$ 。当使用点 $u$ 松弛点 $v$ 时，同时更新 `cnt[v] = cnt[u] + 1`，若 `cnt[v] >= n` 时，就说明存在负环。

  ```cpp
  int spfa(int s) {
      memset(d, 0x3f, sizeof d);
      memset(cnt, 0, sizeof cnt);
      d[s] = 0, cnt[s] = 0;
      queue<int> q;
      q.push(s);
      vt[s] = 1;
      while (!q.empty()) {
          auto u = q.front();
          q.pop();
          vt[u] = 0;
          for (int i = h[u]; i != -1; i = ne[i]) {
              int v = e[i];
              if (d[v] > d[u] + w[i]) {
                  d[v] = d[u] + w[i];
                  cnt[v] = cnt[u] + 1;
                  if (cnt[v] >= n) return true;
                  if (!vt[v]) {
                      q.push(v), vt[v] = 1;
                  }
              }
          }
      }
      return false;
  }
  ```

## Floyd

用来解决全源最短路径问题，即对于图 $G\left( V, E \right)$ ，求任意两点 $u, v$ 之间的最短路径长度。时间复杂度 $O\left( n^3 \right)$ 。由于时间复杂度决定了顶点数 `n` 限制约在 200 以内，故使用邻接矩阵存储图最为合适。

算法思想：如果存在 顶点 $k$ ，使得以 $k$ 为中介点时 顶点 $i$ 和 顶点 $j$ 之间的最短距离缩短，则使用 $k$ 作为 $i$ 和 $j$ 的中介点， 即当 $d[i][k] + d[k][j] < d[i][j]$ 时，令 $d[i][j] = d[i][k] + d[k][j]$ （其中 $d[i][j]$ 表示从顶点 $i$ 到顶点 $v$ 的最短距离）。

```cpp
const int N = 207;
int n, m, d[N][N];

int floyd() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main() {
    scanf("%d %d", &n, &m);
    //初始化
    memset(d, 0x3f, sizeof d);
    for (int i = 0; i < n; i++)
        d[i][i] = 0;
    int x, y, z;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        d[x][y] = min(d[x][y], z); //防止重边，取最小值
    }
    floyd();
}
```