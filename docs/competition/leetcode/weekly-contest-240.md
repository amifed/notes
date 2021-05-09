# [第 240 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-240/)

::: details 个人成绩
$RANK: 311 / 4306$

$SCORE: 12$

$TIME: 0:58:29$
:::

## 1.[人口最多的年份](https://leetcode-cn.com/problems/maximum-population-year/)

枚举

```cpp
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        int ans = 0, max = 0;
        for (int i = 1950; i <= 2050; ++i) {
            int cnt = 0;
            for (auto &v: logs) {
                if (v[0] <= i && i < v[1]) ++cnt;
            }
            if (cnt > max) max = cnt, ans = i;
        }
        return ans;
    }
};
```

```js
/**
 * @param {number[][]} logs
 * @return {number}
 */
var maximumPopulation = function(logs) {
  let ans = 0,
    max = 0
  for (let i = 1950; i <= 2050; ++i) {
    let t = 0
    for (let [s, e] of logs) {
      t += +(s <= i && i < e)
    }
    if (t > max) {
      max = t
      ans = i
    }
  }
  return ans
}
```

- 时间复杂度 $\mathcal{O(n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 2.[下标对中的最大距离](https://leetcode-cn.com/problems/maximum-distance-between-a-pair-of-values/)

双指针

```cpp
class Solution {
public:
    int maxDistance(vector<int>& a, vector<int>& b) {
        int ans = 0;
        int i = 0, j = 0;
        int n = a.size(), m = b.size();
        while (i < n && j < m) {
            if (a[i] <= b[j]) {
                if (i <= j) ans = max(ans, j - i);
                ++j;
            } else {
                ++i;
            }
        }
        return ans;
    }
};
```

```js
/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var maxDistance = function(nums1, nums2) {
  let ans = 0
  let i = 0,
    j = 0
  while (i < nums1.length && j < nums2.length) {
    if (nums1[i] <= nums2[j]) {
      ans = Math.max(ans, j - i)
      ++j
    } else {
      ++i
    }
  }
  return ans
}
```

- 时间复杂度 $\mathcal{O(m+n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 3.[子数组最小乘积的最大值](https://leetcode-cn.com/problems/maximum-subarray-min-product/)

前缀和 + 单调栈

```cpp
const int MOD = 1e9 + 7;
class Solution {
public:
    int maxSumMinProduct(vector<int>& a) {
        const int n = a.size();
        vector<long long> s(n + 1);
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];
        stack<long long> st;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[i] < a[st.top()]) {
                int t = a[st.top()]; st.pop();
                int l = st.empty() ? -1 : st.top(), r = i;
                ans = max(ans, t * (s[r] - s[l + 1]));
            }
            st.push(i);
        }
        while (!st.empty()) {
            int t = a[st.top()]; st.pop();
            int l = st.empty() ? -1 : st.top(), r = n;
            ans = max(ans, t * (s[r] - s[l + 1]));
        }
        return ans % MOD;
    }
};
```

题目原型：[直方图中最大的矩形](https://www.acwing.com/problem/content/133/)

当前值为最小值，左右两边比其小的为边界；

```cpp
using LL = long long;
const int N = 1e5 + 7;
int h[N], l[N], r[N], q[N];
LL s[N];
class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        const int n = nums.size();
        for (int i = 1; i <= n; ++i) {
            h[i] = nums[i - 1], s[i] = s[i - 1] + h[i];
        }
        h[0] = h[n + 1] = 0;
        int tt = 0;
        q[tt] = 0;
        for (int i = 1; i <= n; ++i) {
            while (h[i] <= h[q[tt]]) --tt;
            l[i] = q[tt];
            q[++tt] = i;
        }
        tt = 0;
        q[tt] = n + 1;
        for (int i = n; i; --i) {
            while (h[i] <= h[q[tt]]) --tt;
            r[i] = q[tt];
            q[++tt] = i;
        }
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, h[i] * (s[r[i] - 1] - s[l[i]]));
        }
        return ans % 1000000007;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$;
- 空间复杂度 $\mathcal{O(n)}$;

## 4.[有向图中最大颜色值](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/)

拓扑图使用最长路递推  

```cpp
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int> ind(n), tp;
        vector<vector<int>> g(n), f(n, vector<int> (26));
        for (auto &e: edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            ++ind[v];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (!ind[i]) q.push(i);
        }
        int cnt = 0;
        while (!q.empty()) {
            auto u = q.front(); q.pop(); tp.push_back(u);
            for (auto &v: g[u]) {
                if (!--ind[v]) q.push(v);
            }
        }
        if (tp.size() < n) return -1;
        int ans = 0;
        for (auto &i: tp) {
            f[i][colors[i] - 'a'] = max(f[i][colors[i] - 'a'], 1);
            for (int c = 0; c < 26; ++c) {
                for (auto &j: g[i]) {
                    f[j][c] = max(f[j][c], f[i][c] + (colors[j] - 'a' == c));
                }
                ans = max(ans, f[i][c]);
            }
        }
        return ans;
    }
};
```
