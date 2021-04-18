# [第 50 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-50/)

::: details 个人成绩
$RANK: 826 / 3607$

$SCORE: 12$

$TIME: 0:35:24$
:::

## 1.[最少操作使数组递增](https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-increasing/)

模拟

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] <= nums[i - 1]) {
                ans += nums[i - 1] + 1 - nums[i];
                nums[i] = nums[i - 1] + 1;
            }
        }
        return ans;
    }
};
```

## 2.[统计一个圆中点的数目](https://leetcode-cn.com/problems/queries-on-number-of-points-inside-a-circle/)

暴力，双重循环

```cpp
class Solution {
public:
    int get(int x1, int y1, int x2, int y2) {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> ans;
        for (auto &q : queries) {
            int t = 0;
            for (auto &p: points) {
                if (get(p[0], p[1], q[0], q[1]) <= q[2] * q[2]) ++t;
            }
            ans.push_back(t);
        }
        return ans;
    }
};
```

## 3.[每个查询的最大异或值](https://leetcode-cn.com/problems/maximum-xor-for-each-query/)

题面为给一个数 $x$, 求数字 $k$, 使得 $x ~\text{\^{}}~ k$ 最大，即 $k$ 为对 $x$ 逐位取反;

```cpp
class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        const int n = nums.size();
        for (int i = 1; i < n; ++i) nums[i] ^= nums[i - 1];
        vector<int> ans;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < maximumBit; ++j) {
                nums[i] ^= (1 << j);
            }
            ans.push_back(nums[i]);
        }
        return ans;
    }
};
```