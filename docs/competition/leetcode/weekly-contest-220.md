# Leetcode 第220场周赛题解

## A. [重新格式化电话号码](https://leetcode-cn.com/problems/reformat-phone-number/)

模拟，首先每三个字母一组，将剩余的两个或四个字母两个一组。

```cpp
class Solution {
public:
    string reformatNumber(string number) {
        string s;
        for (auto &c : number) if ('0' <= c && c <= '9') s.push_back(c);
        int n = s.size();
        string ans;
        int i = 0;
        while (i < n && n - i != 2 && n - i != 4) {
            for (int j = 0; i < n && j < 3; ++i, ++j) ans.push_back(s[i]);
            ans.push_back('-');
        }
        while (i < n) {
            for (int j = 0; i < n && j < 2; ++i, ++j) ans.push_back(s[i]);
            ans.push_back('-');
        }
        if (ans.back() == '-') ans.pop_back();
        return ans;
    }
};
```

## B. [1695. 删除子数组的最大得分](https://leetcode-cn.com/problems/maximum-erasure-value/)

双指针滑动窗口，求**若干不同元素** 的子区间最大和

```cpp
const int N = 1e4 + 7;
int p[N];
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& a) {
        int n = a.size();
        memset(p, 0, sizeof p);
        int ans = 0, sum = 0;
        int s = 0, e = 0;
        while (e < n) {
            if (!p[a[e]]) ++p[a[e]], sum += a[e++];
            else --p[a[s]], sum -= a[s++];
            ans = max(ans, sum);
        }
        return ans;
    }
};
```

## C. [1696. 跳跃游戏 VI](https://leetcode-cn.com/problems/jump-game-vi/)

$f[i]$ 表示从下标 0 到 i 的最大得分，状态转移方程为：
$$
f[i] = \underset{max(0, i - k) \le j < i}{max} \{f[i]\} + nums[i]
$$

### 暴力DP （TLE）

```cpp
const int N = 1e5 + 7;
int dp[N];
class Solution {
public:
    int maxResult(vector<int>& a, int k) {
        memset(dp, 0, sizeof dp);
        int n = a.size();
        dp[0] = a[0];
        for (int i = 1; i < a.size(); ++i) {
            int t = -N;
            for (int j = i - 1; j >= 0 && j >= i - k; --j) {
                t = max(t, dp[j]);
            }
            dp[i] += t + a[i];
        }
        return dp[n - 1];
    }
};
```

- 时间复杂度 $O(n ^ 2)$
- 空间复杂度 $O(n)$

### DP + 优先队列

使用优先队列记录 $max(0, i - k) \le j < i$ 中最大值

```cpp
const int N = 1e5 + 7;
int dp[N];
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        memset(dp, 0, sizeof dp);
        priority_queue<pair<int, int>> pq;
        dp[0] = nums[0];
        pq.push({dp[0], 0});
        for (int i = 1; i < n; ++i) {
            while (!pq.empty() && i - pq.top().second > k) pq.pop();
            dp[i] = dp[pq.top().second] + nums[i];
            pq.push({dp[i], i});
        }
        return dp[n - 1];
    }
};
```

- 时间复杂度 $O(n \log n)$
- 空间复杂度 $O(n)$

### DP + 优先队列（空间优化）
由于使用队列来保存前 $k$ 个 $dp$ 值，故 $dp$ 数组可不使用。

```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> pq;
        int ans = nums[0];
        pq.push({ans, 0});
        for (int i = 1; i < n; ++i) {
            while (!pq.empty() && i - pq.top().second > k) pq.pop();
            ans = pq.top().first + nums[i];
            pq.push({ans, i});
        }
        return ans;
    }
};
```

- 时间复杂度 $O(n \log n)$
- 空间复杂度 $O(n)$

### DP + 单调队列（空间优化）
```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        
        deque<pair<int, int>> dq;
        dq.emplace_back(nums[0], 0);
        int ans = nums[0];

        for (int i = 1; i < n; ++i) {
            while (i - dq.front().second > k) dq.pop_front();
            ans = dq.front().first + nums[i];
            while (!dq.empty() && ans >= dq.back().first) dq.pop_back();
            dq.emplace_back(ans, i);
        }
        return ans;
    }
};
```

## D. [1697. 检查边长度限制的路径是否存在](https://leetcode-cn.com/problems/checking-existence-of-edge-length-limited-paths/)

### 在线算法、离线算法
在计算机科学中，在线算法是一种处理输入资料的独特形式，其演算过程中并不要求所有输入资料在算法开始运始之一刻即完备，反而可对逐步输入的资料加以处理并在输入完最后一项资料之后输出运算结果。与之相对的称为离线算法，则假设输入资料在运算开始前已完备。举例：选择排序是离线算法，而插入排序则为在线算法。

在本题中，在线算法即为每次处理一个 query， 对每一个 query 的计算和之后的 query 无关。相反离线算法需要每次把所有信息都收集到，计算当前去 query 的过程中可能需要使用之后的query。

本题属于离线算法。

### 思路与算法
本题两个考察点：
1. 图的连通性，这里使用并查集。
2. 边权的限制，使用离线算法

首先将 $edges$ 按 $dis_i$ 递增排序， $querys$ 也按 $limit_j$ 递增排序。在处理每次询问时，都将小于当前边权限制的边加入并查集中，同时验证连通性。

```cpp
const int N = 1e5 + 7;
int p[N];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
void unionn(int x, int y) {
    p[find(x)] = find(y);
}

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edges, vector<vector<int>>& qs) {
        sort(edges.begin(), edges.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[2] < b[2];
        });

        // 按 query 的索引排序
        vector<int> qidx(qs.size());
        iota(qidx.begin(), qidx.end(), 0);
        sort(qidx.begin(), qidx.end(), [&](const int &i, const int &j) {
            return qs[i][2] < qs[j][2];
        });

        // 初始化并查集
        for (int i = 0; i < n; ++i) p[i] = i;
        
        int i = 0;
        vector<bool> ans(qs.size());
        for (int idx: qidx) {
            while (i < edges.size() && edges[i][2] < qs[idx][2]) {
                unionn(edges[i][0], edges[i][1]);
                ++i;
            }
            ans[idx] = (find(qs[idx][0]) == find(qs[idx][1]));
        }
        return ans;
    }
};
```

