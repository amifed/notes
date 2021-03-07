# [第 230 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-230/)

::: details 个人成绩
$RANK: 386 / 4667$

$SCORE: 13$

$TIME: 1:41:52$
:::

## 1.[检查二进制字符串字段](https://leetcode-cn.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/)

一次遍历

```cpp
class Solution {
public:
    bool checkOnesSegment(string s) {
        int ans = 0;
        char last = '0';
        for (auto &c : s) {
            if (c == '1' && last == '0') ++ans;
            last = c;
        }
        return ans <= 1;
    }
};
```

**复杂度分析**

- 时间复杂度 $\mathcal O(|s|)$
- 空间复杂度 $\mathcal O(1)$

## 2.[构成特定和需要添加的最少元素](https://leetcode-cn.com/problems/minimum-elements-to-add-to-form-a-given-sum/)

计算出差值的绝对值，除于 $limit$ 即为最小添加次数，注意无法整除的情况

```cpp
class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        long long s = goal;
        for (auto &x : nums) s -= x;
        return (abs(s) + limit - 1) / limit;
    }
};
```

## 3.[从第一个节点出发到最后一个节点的受限路径数](https://leetcode-cn.com/problems/number-of-restricted-paths-from-first-to-last-node/)

### 解法一：Dijkstra（堆优化）+ 记忆化搜索

通过 Dijkstra 求出终点 $n$ 到所有节点的最短路径，记忆化搜索满足 $distance$ 递减的路径个数。

```cpp
using PII = pair<int, int>;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
class Solution {
public:
    int ans = 0;
    vector<int> p;
    vector<int> d;
    vector<vector<PII>> g;
    int dfs(int u, int n) {
        if (p[u] != -1) return p[u];
        if (u == n) return 1;
        if (d[u] == INF) return 0;
        int ans = 0;
        for (auto &[v, w]: g[u]) {
            if (d[u] > d[v]) ans = (1LL * ans + dfs(v, n)) % MOD;
        }
        return p[u] = ans;
    }
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        g.resize(n + 1);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }

        // dijkstra
        d.resize(n + 1, INF);
        vector<bool> vt(n + 1, 0);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        d[n] = 0;
        pq.push({0, n});
        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            int u = p.second, dist = p.first;
            if (vt[u])  continue;
            vt[u] = 1;
            for (auto &[v, w]: g[u]) {
                if (d[v] > dist + w) {
                    d[v] = dist + w;
                    pq.push({d[v], v});
                }
            }
        }

        p.resize(n + 1, -1);
        return dfs(1, n);
    }
};
```

#### 复杂度分析

- 时间复杂度 $\mathcal O(E\log V)$
- 空间复杂度 $\mathcal O(E+V)$

### 解法二：Dijkstra（堆优化）+ 动态规划

通过 $\textit{Dijkstra}$ 求出终点 $n$ 到所有节点的最短路径；

在 $\textit{Dijkstra}$ 求解的过程中，路径更新的条件为 点 $u$ 没有被访问过，且存在一条 $\mathcal u\to v$ 的路径，满足 $\mathcal distance[v] > distance[u] + weight[u][v]$ 。

$\textit{Dijkstra}$ 使用的是贪心的思想求最短路问题，且每个节点只会被访问一次；本题求的是节点 $n$ 到其他节点的最短路，在更新路径的过程中，当 $\mathcal{distance[v] < distance[u]}$ 时，说明找到了一条满足条件的路径，累加求和即可，最终结果为 $\mathcal f[1]$。

```cpp
using PII = pair<int, int>;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
    vector<vector<PII>> g(n + 1);
        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }
        vector<int> f(n + 1, 0);
        f[n] = 1;

        // dijkstra
        vector<int> d(n + 1, INF);
        vector<bool> vt(n + 1, 0);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        d[n] = 0;
        pq.push({0, n});
        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            int u = p.second, dist = p.first;
            if (vt[u])  continue;
            vt[u] = 1;
            for (auto &[v, w]: g[u]) {
                if (d[v] > dist + w) {
                    d[v] = dist + w;
                    pq.push({d[v], v});
                }
                if (d[u] < d[v]) f[v] = (1LL * f[u] + f[v]) % MOD;
            }
        }

        return f[1];
    }
};
```

> 求结果的过程类似于使用堆优化的 DP
