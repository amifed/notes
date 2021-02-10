# [第 222 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-222/)

## A. [卡车上的最大单元数](https://leetcode-cn.com/problems/maximum-units-on-a-truck/)

### 解法一： 贪心

#### 算法思想

卡车装的箱子数量和单元数没有关系，所以贪心的选择单元数多的箱子装车。

#### 参考代码

```cpp
class Solution {
public:
    int maximumUnits(vector<vector<int>>& a, int s) {
        sort(a.begin(), a.end(), [](const vector<int> &p, const vector<int> &q) {
            return p[1] > q[1];
        });
        int ans = 0;
        for (auto &v : a) {
            int t = min(v[0], s);
            ans += t * v[1];
            s -= t;
        }
        return ans;
    }
};
```

## B. [大餐计数](https://leetcode-cn.com/problems/count-good-meals/)

### 解法一：枚举 + 哈希表优化

#### 算法思想

使用哈希表统计不同美味程度的餐品个数，对于每种美味程度的餐品枚举 $2^0, 2^1, 2^2, \cdots, 2^{21}$，统计可能组成的组合数目。对一个组合 $(x, y)$，分两种情况：

- 当 $x = y$ 时，即从一组相同的数中选择两两组合，共 $1 + 2 + \cdots + n - 1 = \frac{n(n - 1)}{2}$ 种；
- 当 $x \ne y$ 时，即从两组数中选择两两组合，共 $m * n$ 种。

最后，对于每种组合都计算了两次，结果除以 $2$。

#### 参考代码

```cpp
using LL = long long;
const int MOD = 1e9 + 7;
class Solution {
public:
    int countPairs(vector<int>& ds) {
        unordered_map<int, int> mp;
        for (auto &x : ds) {
            ++mp[x];
        }
        LL ans = 0;
        for (auto [x, v] : mp) {
            for (int k = 0; k <= 21; ++k) {
                int t = (1 << k);
                if (!mp.count(x) || !mp.count(t - x)) continue;
                if (t - x == x) {
                    ans += 1LL * mp[x] * (mp[x] - 1);
                } else {
                    ans += 1LL * mp[x] * mp[t - x];
                }
            }
        }
        return ans / 2 % MOD;
    }
};
```

## C. [将数组分成三个子数组的方案数](https://leetcode-cn.com/problems/ways-to-split-array-into-three-subarrays/)

### 解法一：前缀和 + 二分查找

