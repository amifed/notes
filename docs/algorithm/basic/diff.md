# 差分

## 差分数列

### 定义

数列 $a$, $b$ 满足以下公式：

${b_1 = a_1}$

$b_2 = a_2 - a_1$

$b_3 = a_3 - a_2$

$\vdots$

$b_n = b_n - b_{b-1}$

故 $a_1 = b_1,a_2 = b_1 + b_2,\dots,a_n = b_1 + b_2 + \dots + b_n$; 

即 $a_i = b_1 + b_2 + \dots + b_i$。

其中称 $b$ 为 $a$ 的差分，$a$ 为 $b$ 的前缀和，两者是一组逆运算。

### 用途

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

### 构造

那如何构造数列 $a$, $b$ 呢？

将数列 $a$ 看作原数列，则 $b_i = a_i - a_{i-1}, a_0 = 0, i ≥ 1$。

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
for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];

// 区间更新：[l...r]元素加 c , 1 ≤ l ≤ r ≤ n
insert(l, r, c);

// 还原数列 a，求前缀和
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