# 搜索与图论

## 树与图的存储

树是一种特殊的图，故只考虑图的存储。

- 邻接矩阵

`G[a][b]` 存储 a -> b，如果无权值存储为1，有权值存储为权值即可。

- 邻接表

  `h` 存储每个结点的邻接表的头指针下标；`e` 存储下一个结点的编号；`ne` 存储下一个结点的下标；`w` 存储到下一结点的权值；

```cpp
//对于每一个点 k，开一个单链表，存储 k 所有可以走到的点，h[k] 存储这个单链表的头结点。
const int N = 100; //	结点数据范围
const int M = 1000; // 边数据范围
int h[N], e[M], ne[M], w[M], idx;
//添加边 u -> v, 权值 x
void add(int u, int v, int x) { 
  e[idx] = v, w[idx] = x, ne[idx] = h[u], h[u] = idx++; 
}
int main() {
	//初始化
  idx = 0;
  memset(h, -1, sizeof h);
}
```



## 树与图的遍历

- dfs

```cpp
const int N = 1e5 + 7;
int vt[N];

void dfs(int u) {
    vt[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];
        if (!vt[v]) dfs(v);
    }
}
```

- bfs

```cpp
const int N = 1e5 + 7;
int vt[N];

void bfs(int u) {
  queue<int> q;
  q.push(u);
  vt[u] = 1;
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    for (int i = h[p]; i != -1; i = ne[i]) {
      int v = e[i];
      if (!vt[v]) {
        q.push(v);
        vt[v] = 1;
      }
    }
  }
}
```

## 拓扑排序

```cpp
const int N = 1e5 + 7;
int n, m;
int h[N], e[N], ne[N], idx;
int ind[N]; // 入度

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
```

