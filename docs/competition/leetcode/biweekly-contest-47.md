# [第 46 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-46/)

::: details 个人成绩
$RANK: 191 / 3085$

$SCORE: 12$

$TIME: 0:21:47$
:::

## 1.[找到最近的有相同 X 或 Y 坐标的点](https://leetcode-cn.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/)

枚举

```cpp
class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& ps) {
        int n = ps.size();
        int pos = -1, mi = 0x3f3f3f3f;
        for (int i = 0; i < n; ++i) {
            int a = ps[i][0], b = ps[i][1];
            if (a == x || b ==y) {
                if (abs(a - x) + abs(b - y) < mi) {
                    mi = abs(a - x) + abs(b - y);
                    pos = i;
                }
            }
        }
        return pos;
    }
};
```

### 复杂度分析

- 时间复杂度 $O(n)$
- 空间复杂度 $O(1)$

## 2.[判断一个数字是否可以表示成三的幂的和](https://leetcode-cn.com/problems/check-if-number-is-a-sum-of-powers-of-three/)

### 解法一：递归枚举

```cpp
class Solution {
    vector<int> p;
public:
    bool dfs(int idx, int sum, int n) {
        if (sum >= n) return sum == n;
        if (idx >= p.size()) return 0;
        bool ans = 0;
        ans |= dfs(idx + 1, sum + p[idx], n);
        ans |= dfs(idx + 1, sum, n);
        return ans;
    }
    bool checkPowersOfThree(int n) {
        int x = 1;
        while (x <= n) {
            p.push_back(x);
            x *= 3;
        }
        return dfs(0, 0, n);
    }
};
```

#### 复杂度分析

- 时间复杂度 $O(2^n)$，根据数据范围，n 最大为 16；
- 空间复杂度 $O(1)$，存储 $3$ 的次幂的数组 $p$ 可以看作常数空间。

### 解法二：二进制枚举

```cpp
class Solution {
public:
    bool checkPowersOfThree(int n) {
        int x = 1;
        vector<int> p;
        while (x <= n) {
            p.push_back(x);
            x *= 3;
        } 
        for (int x = 0; x < 1 << p.size(); ++x) {
            int sum = 0;
            for (int i = 0; i < p.size(); ++i) {
                if (x >> i & 1) sum += p[i];
            }
            if (sum == n) return 1;
        }
        return 0;
    }
}; 
```

#### 复杂度分析

- 时间复杂度 $O(2^n)$，根据数据范围，n 最大为 16；
- 空间复杂度 $O(1)$，存储 $3$ 的次幂的数组 $p$ 可以看作常数空间。

## 3.[所有子字符串美丽值之和](https://leetcode-cn.com/problems/problems/sum-of-beauty-of-all-substrings/)

枚举求和

```cpp
class Solution {
public:
    int count(vector<int> &p) {
        int ma = 0, mi = 507;
        for (auto &x : p) {
            ma = max(ma, x);
            if (x != 0) mi = min(mi, x);
        }
        return ma - mi;
    }
    int beautySum(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> p(26, 0);
            for (int j = i; j < n; ++j) {
                ++p[s[j] - 'a'];
                ans += count(p);
            }
        }
        return ans;
    }
};
```

### 复杂度分析

- 时间复杂度 $O(n^2)$，枚举所有子串；
- 空间复杂度 $O(1)$，存储字母出现个数的数组 $p$ 可以看作常数空间。

