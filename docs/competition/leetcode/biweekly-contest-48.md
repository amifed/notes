# [第 48 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-48/)

::: details 个人成绩
$RANK: 716 / 2853$

$SCORE: 7$

$TIME: 0:19:34$
:::

## 1.[字符串中第二大的数字](https://leetcode-cn.com/problems/second-largest-digit-in-a-string/)

模拟

```cpp
class Solution {
public:
    int secondHighest(string s) {
        set<int> st;
        for (auto &c : s) if (isdigit(c)) st.insert(c - '0');
        if (st.size() <= 1) return -1;
        vector<int> v(st.begin(), st.end());
        return v[v.size() - 2];
    }
};
```

```python
class Solution:
    def secondHighest(self, s: str) -> int:
        st = list(set([x for x in list(s) if x.isdigit()]))
        st.sort();
        if len(st) <= 1: return -1
        return int(st[-2])
```

### 复杂度分析

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(n)}$

## 2.[设计一个验证系统](https://leetcode-cn.com/problems/design-authentication-manager/)

```cpp
class AuthenticationManager {
    int ttl;
    unordered_map<string, int> mp;
public:
    AuthenticationManager(int timeToLive) {
        ttl = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        mp[tokenId] = currentTime + ttl;
    }

    void renew(string t, int ct) {
        if (mp.count(t)) {
            if (mp[t] > ct) mp[t] = ct + ttl;
            else mp.erase(t);
        }
    }

    int countUnexpiredTokens(int ct) {
        int ans = 0;
        for (auto &[k, v] : mp) {
            ans += v > ct;
        }
        return ans;
    }
};
```

## 3.[你能构造出连续值的最大数目](https://leetcode-cn.com/problems/maximum-number-of-consecutive-values-you-can-make/)

假设数组中若干个元素可以构造出 $[0, x]$ 范围内的所有整数。如果此时再多选择一个元素 $y$，那么这些元素可以构造出 $[0, x]$ 以及 $[y, y+x]$ 范围内的所有整数。

```cpp
class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int x = 0;
        for (auto &y : coins) {
            if (y > x + 1) break;
            x += y;
        }
        return x + 1;
    }
};
```

### 复杂度分析

- 时间复杂度 $\mathcal{O(n\log{n})}$；
- 空间复杂度 $\mathcal{O(1)}$。

## 4.[N 次操作后的最大分数和](https://leetcode-cn.com/problems/maximize-score-after-n-operations/)

一维状态压缩 DP，枚举每个选择的状态，其中 0 代表已经选择，1 代表未选择；

### 动态规划

```cpp
class Solution {
public:
    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(1 << n);
        for (int x = 0; x < 1 << n; ++x) {
            int cnt = 0;
            for (int i = 0; i < n; ++i) cnt += !(x >> i & 1);
            cnt = cnt / 2 + 1;
            for (int i = 0; i < n; ++i) if (x >> i & 1)
                for (int j = i + 1; j < n; ++j) if (x >> j & 1)
                    f[x] = max(f[x], f[x - (1 << i) - (1 << j)] + gcd(nums[i], nums[j]) * cnt);
        }
        return f[(1 << n) - 1];
    }
};
```

### 动态规划 + 预处理

对 GCD 运算预处理，来降低时间复杂度

```cpp
class Solution {
public:
    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(1 << n);
        vector<vector<int>> g(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                g[i][j] = gcd(nums[i], nums[j]);
        }
        for (int x = 0; x < 1 << n; ++x) {
            int cnt = 0;
            for (int i = 0; i < n; ++i) cnt += !(x >> i & 1);
            cnt = cnt / 2 + 1;
            for (int i = 0; i < n; ++i) if (x >> i & 1)
                for (int j = i + 1; j < n; ++j) if (x >> j & 1)
                    f[x] = max(f[x], f[x - (1 << i) - (1 << j)] + g[i][j] * cnt);
        }
        return f[(1 << n) - 1];
    }
};
```

#### 复杂度分析

- 时间复杂度 $\mathcal{O(2^n*n^2)}$
- 空间复杂度 $\mathcal{O(2^n)}$
