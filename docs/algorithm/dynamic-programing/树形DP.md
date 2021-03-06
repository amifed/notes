# 树形 DP

## [没有上司的舞会](https://www.acwing.com/problem/content/287/)

**状态定义**
$f(x,0)$ 表示当前节点参加舞会时的最大值，$f(x,1)$ 表示当前节点不参加舞会时的最大值；

**状态计算**
对于节点 x，只需考虑它参加舞会 和 不参加舞会 两种情况：

- $f(x,0)$，即不参加舞会，此时 x 的子节点可以参加舞会，可以不参加舞会，取所有子节点的两种情况的最大值再求和

$$
\large\displaystyle f(x,0)=\sum_{s\in Son(x)}\max\{~f(s,0),f(s,1)~\}
$$

- $f(x,1)$，即参加舞会，此时 x 的子节点不可以参加舞会，取所有子节点一种情况的和

$$
\large\displaystyle f(x,1)=h(x)+\sum_{s\in Son(x)}f(s,0)
$$

**初始状态**
对于每个节点，$f(x,0)=0, f(x,1)=h(x)$

**最终结果**
$max\{~f(root,0),f(root,1)~\}$

```cpp
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

```

**复杂度分析**
- 时间复杂度 $\large O(n)$，递归遍历所有节点；
- 空间复杂度 $\large O(n)$，记录每个节点的状态；