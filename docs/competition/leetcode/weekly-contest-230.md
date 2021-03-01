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

### 解法一：双指针 + 贪心

数组 $a$, $b$，其中 $a$ 的和较小，$b$ 的和较大

双指针分别从 数组 $a$ 左侧（较小侧） 和 数组 $b$ 右侧（较大侧）开始移动；

为了让两数组和相等，每次操作可以使较大数变小（最小变为 $1$），或较小数变大（最大变为 $6$），贪心的选择变化差值最大的一边修改；

重复操作直到 指针遍历完数组 或 $sum(a)≥sum(b)$。

<CodeSwitcher :languages="{cpp:'C++',js:'JavaScript'}">
<template v-slot:cpp>

```cpp
class Solution {
public:
    int minOperations(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int sa = accumulate(a.begin(), a.end(), 0);
        int sb = accumulate(b.begin(), b.end(), 0);
        if (sa > sb) return minOperations(b, a);
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
</template>
<template v-slot:js>

```js
/**
 * @param {number[]} a
 * @param {number[]} b
 * @return {number}
 */
var minOperations = function(a, b) {
    const n = a.length, m = b.length;
    a.sort((x, y) => x - y);
    b.sort((x, y) => x - y);
    let sa = a.reduce((sum, x) => sum += x, 0);
    let sb = b.reduce((sum, x) => sum += x, 0);
    if (sa > sb) return minOperations(b, a);
    let i = 0, j = b.length - 1;
    let cnt = 0;
    while (i < n && j >= 0 && sa < sb) {
        if (6 - a[i] > b[j] - 1) {
            sa += 6 - a[i++];
        } else {
            sb -= b[j--] - 1;
        }
        ++cnt;
    }
    while (i < n && sa < sb) {
        sa += 6 - a[i++];
        ++cnt;
    }
    while (j >= 0 && sa < sb) {
        sb -= b[j--] - 1;
        ++cnt;
    }
    return sa >= sb ? cnt : -1;
};
```
</template>
</CodeSwitcher>

- 时间复杂度 $O(n\log n)$
- 空间复杂度 $O(1)$

**补充内容**

对于有序数列 $A = a_1, a_2, \dots, a_n$，$B=b_1,b_2,\dots,b_m$，且$sum(A) <= sum(B)$。

如果让 $sum(A)$ 等于 $sum(B)$ ，有三种可能的操作：

- 将 $sum(A)$ 增加至 $sum(B)$；
- 将 $sum(B)$ 减小至 $sum(A)$；
- 将 $sum(A)$  增大，同时$sum(B)$ 减小，至一个中间值 $sum(C)$；

这些增大缩小可以分布到数列中的每项中，但是由于每项中最小最大值限制，所以第三种方案是一种可能可行的方案，否则其他两种都不可行。

而 $sum(A)，sum(B)$ 向 $sum(C)$ 逼近的时候，一定是选择最大差值从而得到最小操作数。

### 解法二：贪心

统计最大可修改的数量，直接操作，省去排序的过程。

```js
/**
 * @param {number[]} a
 * @param {number[]} b
 * @return {number}
 */
var minOperations = function(a, b) {
    const n = a.length, m = b.length;
    let sa = a.reduce((sum, x) => sum += x, 0);
    let sb = b.reduce((sum, x) => sum += x, 0);
    if (sa > sb) return minOperations(b, a);
    let diff = sb - sa;
    let freq = new Array(6).fill(0);
    for (let x of a) ++freq[6 - x];
    for (let x of b) ++freq[x - 1];
    let cnt = 0;
    for (let i = 5; i >= 1 && diff > 0; --i) {
        while (freq[i] && diff > 0) {
            --freq[i];
            diff -= i;
            ++cnt;
        }
    }
    return diff > 0 ? -1 : cnt;
};
```

复杂度分析

- 时间复杂度：$O(m+n)$，其中 $m$ 和 $n$ 分别是数组 $\textit{nums}_1$​	和 $\textit{nums}_2$ 的长度。

- 空间复杂度：$O(c)$，其中 $c$ 表示数组元素的范围，在本题中 $c=6$。