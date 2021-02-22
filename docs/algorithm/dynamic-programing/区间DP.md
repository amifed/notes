# 区间 DP

区间 DP 需要从 区间长度从小到大来循环

## 石子合并

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 307;

int n;
int s[N];
int f[N][N];

int main() { 
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
    for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
    
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int l = i, r = i + len - 1;
            f[l][r] = 1e9;
            for (int k = l; k < r; ++k) {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
            }
        }
    }
    printf("%d", f[1][n]);
    return 0;
}
```