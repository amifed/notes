# 计数 DP

## 整数划分

### 解法一

定义 $f(i,j)$ 为从前 $i$ 个数中选择总和不超过 $j$ 的划分方案总和，则 $f(n,n)$ 就表示从 $n$ 个数中选择总和为 $n$ 的划分方案的和。

对于 $f(i, j)$，即第 $i$ 个数，我们可以选择使用 $0, 1, 2, \cdots, k$ 次参与划分：

- 划分 $0$ 次：那 $f(i, j)$ 应该为前 $i - 1$ 个数中总和为 $j$ 的数的划分方案之和，即 $f(i, j) =  f(i - 1, j)$；
- 划分 $1$ 次，此时总和应为 $j-i$ ，那 $f(i, j)$ 应该为前 $i - 1$ 个数字中总和为 $j - i$ 的划分方案之和，即 $f(i,j) = f(i-1,j-i)$
- $\dots$
- 划分 $k$ 次，那此时总和应该为 $j-ki$（$j-ki≥0$） ，那 $f(i, j)$ 应该为前 $i - 1$ 个数字中总和为 $j - ki$ 的划分方案之和，即 $f(i,j) = f(i-1,j-ki)$

最后讨论完所有情况，$f(i, j)$ 为前 $i$ 个数字中总和为 $j$ 的划分方案之和，所以 $f(i, j)$ 应对 $k+1$ 种情况求和。

**边界条件**

当 $i=0,j=0$，即 $0$ 个数字总和为 $0$ 的划分方案只有一种，即 $f(0,0)=1$。

**状态转移方程**

$f(i,j)=f(i-1,j)+f(i-1,j-i)+f(i-1,j-2i)+\cdots+f(i-1,j-ki)，1≤i≤n，j-ki≥0$

#### 朴素写法

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 7;
const int MOD = 1e9 + 7;

int n;
int f[N][N];

int main() {
    cin >> n;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k * i <= j; ++k) {
                f[i][j] = (f[i][j] + f[i - 1][j - k * i]) % MOD;
            }
        }
    }
    cout << f[n][n];
    return 0;
}
```

#### 时间优化

$f(i,j)=f(i-1,j)+f(i-1,j-i)+f(i-1,j-2i)+\cdots+f(i-1,j-ki)，(1)$

$f(i,j-i)=f(i-1,j-i)+f(i-1,j-2i)+\cdots+f(i-1,j-ki)，(2)$

合并 $(1),(2)$ 式可得 $f(i,j)=f(i-1,j)+f(i,j-i)$；

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 7;
const int MOD = 1e9 + 7;

int n;
int f[N][N];

int main() {
    cin >> n;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
            if (j >= i) f[i][j] = (f[i][j] + f[i][j - i]) % MOD;
        }
    }
    cout << f[n][n];
    return 0;
}
```
#### 空间优化
```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 7;
const int MOD = 1e9 + 7;

int n;
int f[N];

int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[j] = (f[j] + f[j - i]) % MOD;
        }
    }
    cout << f[n];
    return 0;
}
```

### 解法二

另一种定义状态的方式，

$f[i][j]$  表示总和是 $i$ ，且恰好表示成 $j$ 个数的和的方案总数；

状态可分为两种情况，划分方案中包含 $1$ 和 不包含 $1$。

状态转移方程： $f[i][j]=f[i-1][j-1]+f[i-j][j]$；
最终方案数为 $\displaystyle\sum_{i=1}^n f[n][i]$。

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 7;
const int MOD = 1e9 + 7;

int n;
int f[N][N];

int main() {
    cin >> n;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % MOD;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = (ans + f[n][i]) % MOD;
    cout << ans;
    return 0;
}
```

