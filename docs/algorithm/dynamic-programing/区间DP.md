# 区间 DP

区间 DP 需要从 区间长度从小到大来循环

## [石子合并]()

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

## [执行乘法运算的最大分数](https://leetcode-cn.com/problems/maximum-score-from-performing-multiplication-operations/)

**记忆化搜索**

```cpp
const int N = 1e3 + 7;
int f[N][N];
class Solution {
public:
    int n, m;
    int dfs(int i, int j, vector<int> &nums, vector<int> &mul) {
        if (j >= m) return 0;
        if (f[i][j] != 0x3f3f3f3f) return f[i][j];
        return f[i][j] = max(
            dfs(i + 1, j + 1, nums, mul) + nums[i] * mul[j],
            dfs(i, j + 1, nums, mul) + nums[n - j + i - 1] * mul[j]
        );
    }
    int maximumScore(vector<int>& nums, vector<int>& mul) {
        n = nums.size(), m = mul.size();
        memset(f, 0x3f, sizeof f);
        return dfs(0, 0, nums, mul);
    }
};
```

**动态规划**

$f(i,j)$ 表示 $nums$ 从 $i$ 开始，$multiplier$ 从 $j$ 开始的所有可能方案的最大分数，则 $nums$ 末尾使用的元素个数为 $j-i$，因此最后一个可取元素为 $nums[n-(j-i)-1]$；

对 $f(i,j)$ 有两种转移方案：

- 选开头的 $nums[i]$ ，剩下的方案数表示为 $f(i+1,j+1)$;
- 选择结尾的 $nums[n-(j-i)-1]$，剩下的方案数表示为 $f(i,j+1)$。

对两种情况求最大值即可。
最终结果为 $f(0,0)$。

```cpp
const int N = 1e3 + 7;
int f[N][N];
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& mul) {
        int n = nums.size(), m = mul.size();
        memset(f, 0, sizeof f);
        for (int j = m - 1; j >= 0; --j) {
            for (int i = j; i >= 0; --i) {
                f[i][j] = max(
                    f[i + 1][j + 1] + nums[i] * mul[j],
                    f[i][j + 1] + nums[n - j + i - 1] * mul[j]);
            }
        }
        return f[0][0];
    }
};
```
