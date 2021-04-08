# [第 49 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-49/)

::: details 个人成绩
$RANK: 244 / 3193$

$SCORE: 12$

$TIME: 0:36:21$
:::

## 1.[判断国际象棋棋盘中一个格子的颜色](https://leetcode-cn.com/problems/determine-color-of-a-chessboard-square/)

所在行列相加，和为奇数为黑色，和为偶数为白色

```cpp
class Solution {
public:
    bool squareIsWhite(string c) {
      return !(c[0] - 'a' + c[1] - '0' & 1);
    }
};
```

### 复杂度分析

- 时间复杂度 $\mathcal{O(1)}$
- 空间复杂度 $\mathcal{O(1)}$

## 2.[句子相似性 III](https://leetcode-cn.com/problems/sentence-similarity-iii/)

双指针

```js
/**
 * @param {string} sentence1
 * @param {string} sentence2
 * @return {boolean}
 */
var areSentencesSimilar = function(s1, s2) {
    if (s1 == s2) return true
    s1 = s1.split(' ')
    s2 = s2.split(' ')
    const m = s1.length, n = s2.length
    let l1 = 0, l2 = 0
    while (l1 < m && l2 < n && s1[l1] == s2[l2]) ++l1, ++l2
    let r1 = m - 1, r2 = n - 1
    while (r1 >= 0 && r2 >= 0 && s1[r1] == s2[r2]) --r1, --r2
    return l1 > r1 || l2 > r2
};
```

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(|s1|+|s2|)}$

## 3.[统计一个数组中好对子的数目](https://leetcode-cn.com/problems/count-nice-pairs-in-an-array/)

$nums[i]+rev(nums[j])==nums[j]+rev(nums[i])$

等价转化为

$nums[i]-rev(nums[i])==nums[j]-rev(nums[j])$

统计 $nums[i]-rev(nums[i])$ 的个数，求两两组合的组合数 $=\displaystyle{\frac{t(t-1)}{2}}$

```cpp
using ll = long long;
const int mod = 1e9 + 7;
class Solution {
public:
    int rev(int x) {
        int ans = 0;
        while (x) {
            ans = ans * 10 + x % 10;
            x /= 10;
        }
        return ans;
    }
    int countNicePairs(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int x : nums) ++mp[x - rev(x)];
        ll ans = 0;
        for (auto &p : mp) {
            ll t = p.second;
            ans = (ans + t * (t - 1) / 2) % mod;
        }
        return ans % mod;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$；
- 空间复杂度 $\mathcal{O(n)}$。

## 4.[得到新鲜甜甜圈的最多组数](https://leetcode-cn.com/problems/maximum-number-of-groups-getting-fresh-donuts/)


- 时间复杂度 $\mathcal{O()}$
- 空间复杂度 $\mathcal{O()}$
