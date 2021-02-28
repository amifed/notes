# [第 230 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-230/)

::: details 个人成绩
$RANK: 645 / 3727$

$SCORE: 12$

$TIME: 1:28:17$
:::

## 1.[统计匹配检索规则的物品数量](https://leetcode-cn.com/problems/merge-strings-alternately/)

分类计数

```cpp
class Solution {
public:
    int countMatches(vector<vector<string>>& items, string rk, string rv) {
        int ans = 0;
        for (auto &v : items) {
            if (rk == "type") ans += rv == v[0];
            if (rk == "color") ans += rv == v[1];
            if (rk == "name") ans += rv == v[2];
        }
        return ans;
    }
};
```

## 2.[最接近目标价格的甜点成本](https://leetcode-cn.com/problems/closest-dessert-cost/)

递归枚举配料的选择个数

```cpp
class Solution {
public:
    int ret = 0x3f3f3f3f;
    void dfs(vector<int> &tc, int idx, int sum, int tar) {
        if (idx >= tc.size()) {
            if (abs(sum - tar) < abs(ret - tar) || abs(sum - tar) == abs(ret - tar) && sum < ret) {
                ret = sum;
            }
            return;
        }
        for (int i = 0; i <= 2; ++i) {
            dfs(tc, idx + 1, sum + tc[idx] * i, tar);
        }
    }
    int closestCost(vector<int>& bc, vector<int>& tc, int tar) {
        int n = bc.size(), m = tc.size();
        for (int i = 0; i < n; ++i) {
            dfs(tc, 0, bc[i], tar);
        }
        return ret;
    }
};
```

## 3.[通过最少操作次数使数组的和相等](https://leetcode-cn.com/problems/equal-sum-arrays-with-minimum-number-of-operations/)

双指针 + 贪心

数组 $a$, $b$，其中 $a$ 的和较小，$b$ 的和较大

双指针分别从 数组 $a$ 左侧（较小侧） 和 数组 $b$ 右侧（较大侧）开始移动；

为了让两数组和相等，每次操作可以使较大数变小（最小变为 $1$），或较小数变大（最大变为 $6$），贪心的选择变化差值最大的一边修改；

重复操作直到 指针遍历完数组 或 $sum(a)≥sum(b)$。

```cpp
class Solution {
public:
    int minOperations(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int sa = accumulate(a.begin(), a.end(), 0);
        int sb = accumulate(b.begin(), b.end(), 0);
        if (sa > sb) swap(sa, sb), swap(a, b);
        int i = 0, j = b.size() - 1;
        int cnt = 0;
        while (i < a.size() && 0 <= j && sa < sb) {
            if (6 - a[i] > b[j] - 1) { // 选择变化差值最大的一边
                sa += 6 - a[i++];
            } else sb -= b[j--] - 1;
            ++cnt;
        }
        while (i < a.size() && sa < sb) {
            sa += 6 - a[i++];
            ++cnt;
        }
        while (0 <= j && sa < sb) {
            sb -= b[j--] - 1;
            ++cnt;
        }
        return sa >= sb ? cnt : -1;
    }
};
```
