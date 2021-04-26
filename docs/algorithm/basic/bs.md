# 二分查找

## 算法

### 整数

```cpp
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid] 和 [mid + 1, r]时使用：
// 求区间的左边界
int bsearch_1(int l, int r) {
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;	// 向左逼近左边界
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1] 和 [mid, r]时使用：
// 求区间的右边界
int bsearch_2(int l, int r) {
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;	//向右逼近右边界
        else r = mid - 1;
    }
    return l;
}
```

> bsearch_2 中，`mid = l + r + 1 >> 1`，因为 整数除法向下取整，故当区间只剩下两个元素时，`mid = l + r >> 1` 会导致 `l == mid`，满足条件时划分区间一直为 `[l,r]`，从而陷入死循环。

### 浮点数

```cpp
const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求，一般比题目精度小两位
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double bsearch_3(double l, double r)
{
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return l;
}
```

> 注意浮点数二分只需 `l = mid` 或 `r = mid`，不能 `+1`，`-1`，也不需要考虑边界。

## 问题

### 二分查找转化为判定问题

相关题目：

- [LeetCode 1011. 在 D 天内送达包裹的能力](https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/)
