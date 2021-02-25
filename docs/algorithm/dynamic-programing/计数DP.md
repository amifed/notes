# 计数 DP

## 整数划分

### 解法一

完全背包的思想定义状态

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
状态转移方程： $f[i][j]=f[i-1][j-1]+f[i-j][j]$；
最终方案数为 $\displaystyle\sum_{i=1}^n f[n][i]$

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