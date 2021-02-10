# [第 224 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-224/)

## A. [可以形成最大正方形的矩形数目](https://leetcode-cn.com/problems/number-of-rectangles-that-can-form-the-largest-square/)

### 解法一：统计

记录每个可分割矩形的边长

```cpp
class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        unordered_map<int, int> p;
        int ans = 0;
        for (auto &rect : rectangles) {
            ++p[min(rect[0], rect[1])];
            ans = max(ans, min(rect[0], rect[1]));
        }
        return p[ans];
    }
};
```

## B. [同积元组](https://leetcode-cn.com/problems/tuple-with-same-product/)

### 解法一：组合 + 哈希

由 $a * b = c * d$，可知即是从数组中找到乘积相同的两个数的组合，使用哈希表统计，对于每个乘积求  $C_{n}^{2}$，最后对于每种组合 $(a, b, c, d)$ 可以写出 8 种。

```cpp
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> p;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ++p[nums[i] * nums[j]];
            }
        }
        int ans = 0;
        for (auto &[f, s] : p) {
            ans += s * (s - 1) / 2;
        }
        return ans * 8;
    }
};
```

## C. [重新排列后的最大子矩阵](https://leetcode-cn.com/problems/largest-submatrix-with-rearrangements/)

```cpp
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<int> sr(m, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                sr[i] += mat[i][j];
            }
        }
        vector<vector<int>> sl(m, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = m - 1; j >= 0; --j) {
                if (!mat[j][i]) sl[j][i] = 0;
                else sl[j][i] = (j == m - 1 ? 0 : sl[j + 1][i]) + 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            sort(sl[i].rbegin(), sl[i].rend());
            for (int j = 0; j < sr[i]; ++j) ans = max(ans, (j + 1) * sl[i][j]);
        }
        return ans;
    }
};
```

