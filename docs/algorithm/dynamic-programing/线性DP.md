# 线性 DP 问题

## 数字三角形

## 最长上升子序列

### 朴素写法

- 时间复杂度 $O(n^2)$

  状态数量 \* 每个状态计算的数量

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3 + 7;

int n, p[N];
int f[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (p[i] > p[j]) f[i] = max(f[i], f[j] + 1);
        }
    }
    cout << *max_element(f, f + n);
    return 0;
}
```

### 优化

基于贪心

```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 7;

int n, q[N], idx;

int main() {
    cin >> n;
    q[0] = -1e9 - 7, idx = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        int l = 0, r = idx;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (q[mid] < x) l = mid;
            else r = mid - 1;
        }
        idx = max(idx, r + 1);
        q[r + 1] = x;
    }
    cout << idx;
    return 0;
}
```

## 最长公共子序列

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 7;

int n, m;
char s[N], t[N];
int f[N][N];

int main() {
    cin >> n >> m;
    cin >> s >> t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1]) {
                f[i][j] = max(f[i][j], f[i-1][j-1]+1);
            } else {
                f[i][j] = max(f[i-1][j], f[i][j-1]);
            }
        }
    }
    cout << f[n][m];
    return 0;
}
```
