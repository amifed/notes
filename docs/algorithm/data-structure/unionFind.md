# 并查集

- 朴素并查集

```cpp
const int N = 1e5 + 7;
int p[N];
int n;

// 初始化
for	(int i = 0; i < n; ++i) p[i] = i;

// 查
int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

// 并
void unionn(int x, int y) {
  p[find(x)] = find(y);
}
```

**类写法的 UnionFind 模版**
```cpp
class UnionFind {
private:
    int n;
    vector<int> p; 

public:
    vector<int> sz; // 联通分量内点数
    int cnt; // 联通分量数
    UnionFind(int _n) : n(_n), cnt(_n), p(_n), sz(_n, 1) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }

    int find(int x) { return x != p[x] ? p[x] = find(p[x]) : p[x]; }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        if (sz[x] < sz[y]) swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
        --cnt;
        return 1;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};
```

- 维护集合数量

```cpp
const int N = 1e5 + 7;
int p[N], size[N];
int n;

// 初始化
for	(int i = 0; i < n; ++i) p[i] = i, size[i] = 1;

// 查
int find(int x) {
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

// 并
void unionn(int x, int y) {
  int rx = find(x), ry = find(y);
  if (rx != ry) size[ry] += size[rx], p[rx] = ry; // 只更新根结点数量
}
```

- 维护到根结点距离

```cpp
const int N = 1e5 + 7;
int p[N], d[N];
int n;

// 初始化
for	(int i = 0; i < n; ++i) p[i] = i, d[i] = 0;

// 查
int find(int x) {
  if (p[x] != x) {
    int t = find(p[x]);
    d[x] += d[p[x]];
    p[x] = t;
  }
  return p[x];
}

// 并
void unionn(int x, int y) {
  int px = find(x), py = find(y);
  p[px] = py;
  d[px] = distance // 根据具体问题，设置 px 的偏移量
}
```