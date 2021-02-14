# [第 228 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-228/)

::: details 个人成绩
$AC: 1,2,4$

$RANK: 421 / 2483$

$TIME:  1:10:27$
:::

## 1.[生成交替二进制字符串的最少操作数](https://leetcode-cn.com/problems/minimum-changes-to-make-alternating-binary-string/)

统计奇数位不为 $0$ 偶数位不为 $1$ 或 奇数位不为 $1$ 偶数位不为 $0$ 的个数，取最小值.

```cpp
class Solution {
public:
    int minOperations(string s) {
        int t1 = 0, t2 = 0;
        for (int i = 0; i < s.size(); ++i) {
            t1 += s[i] != (i % 2 + '0');
            t2 += s[i] == (i % 2 + '0');
        }
        return min(t1, t2);
    }
};
```

## 2.[统计同构子字符串的数目](https://leetcode-cn.com/problems/count-number-of-homogenous-substrings/)

连续相等字符串求组合和，设连续相等字符长度为 $n$, 连续子序列个数为 $(1+n)*n/2$;

```cpp
const int MOD = 1e9 + 7;
class Solution {
public:
    int countHomogenous(string s) {
        int l = 0, r = 0;
        int ans = 0;
        while (r < s.size()) {
            while (r < s.size() && s[l] == s[r]) ++r;
            ans += 1LL * (1 + r - l) * (r - l) / 2 % MOD;
            l = r;
        }
        return ans;
    }
};
```

## 3.[袋子里最少数目的球](https://leetcode-cn.com/problems/minimum-limit-of-balls-in-a-bag/)

第一反应为贪心，但是数据量上贪心不可行，而且贪心的思路是不对的。

将问题转化为 **给定 $\textit{maxOperations}$ 次操作次数，能否可以使得单个袋子里球数目的最大值不超过 $k$。**

由于$k$ 就减小, 操作次数增多，因此 $k$ 具有单调性，可以通过二分答案求解。

如果单个袋子有 $x$ 个球，每次分出 $k$个球，需要操作次数 $\lfloor \frac{x-1}{k} \rfloor$，总共操作次数为 $\sum \lfloor \frac{x-1}{k} \rfloor$

> 一般情况下，最大化最小值、最小化最大值都可用二分求解。

```cpp
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = l + (r - l >> 1);
            int t = 0;
            for (auto x : nums) t += (x - 1) / mid;
            if (t <= maxOperations) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};
```

## 4. [一个图中连通三元组的最小度数](https://leetcode-cn.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/)

用邻接矩阵存储图，记录每个点的度，枚举所有三元组，计算满足条件的三元组的度数 $totle = deg[i] + deg[j] + deg[k] - 6$;

> 根据数据范围 $n≤400$ 可知 $O(n^3)$ 满足

```cpp
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n + 1, vector<int> (n + 1, 0));
        vector<int> deg(n + 1, 0);
        for (auto &e : edges) {
            g[e[0]][e[1]] = 1;
            g[e[1]][e[0]] = 1;
            ++deg[e[0]], ++deg[e[1]];
        }
        int ans = 1e9;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (!g[i][j]) continue;
                for (int k = j + 1; k <= n; ++k) {
                    if (g[j][k] && g[k][i]) {
                        int t = deg[i] + deg[j] + deg[k] - 6;
                        ans = min(ans, t);
                    }
                }
            }
        }
        return ans == 1e9 ? -1 : ans;
    }
};
```

