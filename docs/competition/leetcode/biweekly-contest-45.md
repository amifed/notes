# [第 45 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-45/)

::: details 个人成绩
$AC: 1,3$

$RANK: 797 / 1676$

$TIME: 0:19:29$
:::

## 1. [5657. 唯一元素的和](https://leetcode-cn.com/problems/sum-of-unique-elements/)

计数求和

```cpp
class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> p;
        for (auto &x : nums) ++p[x];
        int ans = 0;
        for (auto &m : p) if (m.second == 1) ans += m.first;
        return ans;
    }
};
```

## 2. [任意子数组和的绝对值的最大值](https://leetcode-cn.com/problems/maximum-absolute-sum-of-any-subarray/)

求绝对值最大就是求最大值或最小值再取绝对值，即[最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

#### 最大子序和参考代码（空间优化）
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN, f = 0;
        for (auto &x : nums) {
            f = max(x, f + x);
            ans = max(ans, f);
        }
        return ans;
    }
};
```

本题求最大子序和和最小子序和，再取二者绝对值的最大值即可。

```cpp
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int ma = INT_MIN, mi = INT_MAX;
        int f1 = 0, f2 = 0;
        for (auto &x : nums) {
            f1 = max(x, f1 + x);
            f2 = min(x, f2 + x);
            ma = max(ma, f1), mi = min(mi, f2);
        }
        return max(abs(ma), abs(mi));
    }
};
```

## 3. [删除字符串两端相同字符后的最短长度](https://leetcode-cn.com/problems/minimum-length-of-string-after-deleting-similar-ends/) 

双指针模拟

```cpp
class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int lc = s[l], rc = s[r];
            int tl = l, tr = r;
            while (l <= r && s[l] == rc) ++l;
            while (l <= r && s[r] == lc) --r;
            if (tl == l || tr == r) break;
        }
        return r - l + 1;
    }
};
```

