# 基础算法

## 快速排序

这种写法只能保证 `q[l...j] <= x`、`q[j+1...r] >= x`，并不能保证每次排序 x 都能放在最终位置。

```cpp
const int N = 1e5 + 7;
int n, q[N];
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}
```

> 枢轴选择中间位置的值能避免在极端情况下（数组元素全部相等）退化成 $O(n^2)$ 的时间复杂度。

另一种相同的写法，划分区间为 `q[l, i - 1]`、`q[i, r]`；

```cpp
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int x = q[l + r + 1 >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, i - 1), quick_sort(q, i, r);
}
```

> 注意枢轴的选择为 `l + r + 1 >> 1`， 防止划分为 `[]，[l, r]`造成死循环

## 归并排序

```cpp
const int N = 1e5 + 7;
int n, q[N], tmp[N];
void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int m = l + r >> 1;
    merge_sort(q, l, m), merge_sort(q, m + 1, r);
  
    int k = 0, i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= m) tmp[k++] = q[i++];
    while (j <= r)tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
}
```

## 二分查找

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

## 高精度加法

```cpp
// C = A + B, A >= 0, B >= 0
vector<int> add(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || i < B.size(); i++) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t) C.push_back(t);
    return C;
}
```

## 高精度减法

```cpp
// A >= B
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--)
        if (A[i] != B[i]) return A[i] > B[i];
    return true;
}
// C = A - B, A >= B, A >= 0, B >= 0
vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < A.size(); i++) {
        t = A[i] - t; //处理借位
        if (i < B.size()) t -= B[i];
        c.push_back((t + 10) % 10); // t >= 0 || t < 0
        t = t < 0; // 	借位
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}
```

## 高精度乘法

高精度乘低精度

```cpp
// C = A * b, A >= 0, b > 0
vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || t; i++) {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
```

## 高精度除法

高精度除低精度

```cpp
// A / b = C …… r, A >= 0, b > 0
vector<int> div(vector<int> &A, int b, int &r) {
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
```

## 一维前缀和

```cpp
// 前缀和数组
s[i] = a[0] + a[1] + a[2] + ... + a[i];

// 初始化前缀和数组
s[0] = 0;
for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];

// 区间求和 [l...r]
s[l...r] = s[r] - s[l - 1];
```

## 二维前缀和

```cpp
// 二维数组 a[1...n][1...m]
// s[i, j] = 第i行j列格子左上部分所有元素的和
for (int i = 1; i <= n; i++) 
  for (int j = 1; j <= m; j++)
    s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];

// 以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵的和为：
s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
```

## 差分

- **定义：**

数列 $a$, $b$ 满足以下公式：

${b_1 = a_1}$

$b_2 = a_2 - a_1$

$b_3 = a_3 - a_2$

$\vdots$

$b_n = b_n - b_{b-1}$

故 $a_1 = b_1,a_2 = b_1 + b_2,\dots,a_n = b_1 + b_2 + \dots + b_n$; 

即 $a_i = b_1 + b_2 + \dots + b_i$。

其中称 $b$ 为 $a$ 的差分，$a$ 为 $b$ 的前缀和，两者是一组逆运算。

- **用途：**

当要区间更新数列 $a$ 的值时（ 序列中 $[l, r]$ 之间的每个数加上 $c$ ），最简单的做法是遍历数组，在指定区间更新，时间复杂度 $O(n)$; 

而差分数组可以实现 $O(1)$ 的时间复杂度更，公式为 $b_l += c, \ b_{r + 1} -= c$ ;

此时 数列 $b$ 为：

${b_1 = a_1}$

$b_2 = a_2 - a_1$

$\vdots$

$b_l = b_l - b_{l-1} + c$

$\vdots$

$b_{r+1} = b_{r+1} - b_r - c$

$\vdots$

$b_n = b_n - b_{b-1}$

则，数列 $a$ 如下：

$a_1 = b_1$

$a_2 = b_1 + b_2$

$\vdots$

$a_l = b_1 + b_2 + \dots + b_l + c$

$a_{l+1} = b_1 + b_2 + \dots + b_l + c + b_{l+1}$

$\vdots$

$a_r =  b_1 + b_2 + \dots + b_l + c + \dots + b_r$

$a_{r+1} = b_1 + b_2 + \dots + b_l + c + \dots + b_r + b_{r+1} - c = b_1 + b_2 + \dots + b_{r+1}$

可以发现，通过两个式子就实现了在数列 $a$ 上的区间更新；

- 构造

那如何构造数列 $a$, $b$ 呢？

将数列 $a$ 看作原数列，直接使用更新公式即可构建数列 $b$；

初始化数列 $b$ 都为 0, 公式为 $b_i = b_i + a_i, b_{i+1} = b_{i+1}  - a_i$

$b_1 = b_1 + a_1,  b_2 = b_2 - a_1$  $\Longrightarrow$  $b_1 = a_1, b_2 = -a_1$

$b_2 = b_2 + a_2, b_3 = b_3 - a_2$  $\Longrightarrow$  $b_2 = -a_1 + a_2 = a_2 - a_1, b_3 = -a_2$

$\vdots$

```cpp
int n, m;
int a[N], b[N];

// 区间更新
void insert(int l, int r, int c) {
    b[l] += c;
    b[r + 1] -= c;
}

// 读入数列 a
for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
// 构造数列 b
memset(b, 0, sizeof b);
for (int i = 1; i <= n; i++) insert(i, i, a[i]);
// 区间更新：[l...r]元素加 c 
insert(l, r, c);
// 还原数列 a
for (int i = 1; i <= n; i++) a[i] = a[i - 1] + b[i]; // 或 b[i] += b[i - 1]
```

## 差分矩阵

和差分数列相同，适用于二维数组的区间更新。更新后的原数组通过二维前缀和求解

```cpp
#include <iostream>

const int N = 1e3 + 7;

int n, m, q, a[N][N], b[N][N];
// 区间更新
void insert(int x1, int y1, int x2, int y2, int c) {
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;
}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]); 
            insert(i, j, i, j, a[i][j]); // 构造 b 矩阵
        }

    while (q--) {
        int x1, x2, y1, y2, c;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
        insert(x1, y1, x2, y2, c); // 区间更新
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1]; //前缀和求更新后矩阵
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

## 双指针

双指针通常用来优化算法的时间复杂度。

```cpp
for (int i = 0, j = 0; i < n; i++ ) {
    while (j < i && check(i, j)) j++ ;
    // 具体问题的逻辑
}
```

## 二进制

```cpp
// n 的第 k 位数字是 ？ 
n >> k & 1
// 返回n的最后一位1
lowbit(n) = n & -n
```

## 离散化

数据范围大，但是很稀疏时，使用离散化来解决问题。

例如：

```
假定有一个无限长的数轴，数轴上每个坐标上的数都是0。
现在，我们首先进行 n 次操作，每次操作将某一位置 x 上的数加 c。
接下来，进行 m 次询问，每个询问包含两个整数l和r，你需要求出在区间[l, r]之间的所有数的和。
```

由于数据很大，无法使用数组来直接存储，因此需要离散化处理。

离散化即 将例如 `[1, 5, 100, 3000, 60000, ...]`等**有序且稀疏**的数列离散到数组中，用下标`[1, 2, 3, 4, 5]`来映射这些数字。要获取这些数字的下标，可以使用二分查找。

```cpp
vector<int> all; // 存储所有待离散化的值
sort(all.begin(), all.end()); // 排序
alls.erase(unique(all.begin(), all.end()), all.end());   // 去重

// 二分求出x对应的离散化的值, 即离散数组的下标
int find(int x) // 找到第一个大于等于x的位置
{
    int l = 0, r = all.size() - 1;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (all[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1; // 映射到1, 2, ...n
}
```

例题代码：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 3e5 + 7;
using PII = pair<int, int>;

int n, m, a[N], s[N];
vector<int> all;
vector<PII> add, query;

int find(int x) {
    int l = 0, r = all.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (all[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int x, c;
        scanf("%d%d", &x, &c);
        all.push_back(x);
        add.push_back({x, c});
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        all.push_back(l);
        all.push_back(r);
        query.push_back({l, r});
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (auto &p : add) {
        int i = find(p.first);
        a[i] += p.second;
    }

    for (int i = 1; i <= all.size(); i++) s[i] = s[i - 1] + a[i];

    for (auto &p : query) {
        int l = find(p.first), r = find(p.second);
        printf("%d\n", s[r] - s[l - 1]);
    }   
    return 0;
}
```

## 区间合并

```cpp
// 将所有存在交集的区间合并
vector<PII> merge(vector<PII> &segs) {
    vector<PII> ans;
    sort(segs.begin(), segs.end());
    int st = -INF, ed = -INF;
    for (auto &seg : segs) {
        if (ed < seg.first) {
            if (st != -INF) ans.push_back({st, ed});
            st = seg.first, ed = seg.second;
        } else
            ed = max(ed, seg.second);
    }
    if (st != -INF) ans.push_back({st, ed});
    return ans;
}
```

