# [第 236 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-236/)

## 1.[数组元素积的符号](https://leetcode-cn.com/problems/sign-of-the-product-of-an-array/)

符号计算

```cpp
class Solution {
public:
    int arraySign(vector<int>& nums) {
        int x = 1;
        for (auto &a : nums) {
            if (a > 0) x *= 1;
            else if (a < 0) x *= -1;
            else return 0;
        }
        return x;
    }
};
```

## 2.[找出游戏的获胜者](https://leetcode-cn.com/problems/find-the-winner-of-the-circular-game/)

### 解法一：模拟

```cpp
class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        int p = 0;
        for (int i = 0; i < n - 1; ++i) {
            p = (p + k - 1) % a.size();
            a.earse(a.begin() + p);
        }
        return a[0];
    }
};
```

- 时间复杂度 $\mathcal{O(n^2)}$
- 空间复杂度 $\mathcal{O(n)}$

### 解法二：约瑟夫环

$f(N,M)=(f(N−1,M)+M)\%N$

```cpp
class Solution {
public:
    int f(int n, int k) {
        if (n == 1) return 0;
        return (f(n - 1, k) + k) % n;
    }
    int findTheWinner(int n, int k) {
        return f(n, k) + 1;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(1)}$

## 3.[最少侧跳次数](https://leetcode-cn.com/problems/minimum-sideway-jumps/)

动态规划

### 状态定义

$f[i][j]$ 表示在 i 处第 j 个跑道上最少侧跳次数

### 状态计算

当前跑道上有障碍物时，$i$ 处第 $j$ 个跑道不存在路径，设为 $\infty$；

当前跑道上无障碍物时，$i$ 处第 $j$ 个跑道可以从 $i-1$ 处第 $j$ 个跑道直接转移（不需要侧跳），或者从其他跑道侧跳一次；

### 初始状态

第 $0$ 处时，从第 $2$ 条跑道出发，$f[0][1]=0$，第 $1, 3$ 条跑道需要侧跳一次，$f[0][0]=f[0][2]=1$

### 最终结果

最后一处 $3$ 条跑道上的最小值，$min(f[n-1])$

```cpp
const int N = 5e5 + 7;
int f[N][3];
class Solution {
public:
    int minSideJumps(vector<int>& b) {
        const int n = b.size();
        memset(f, 0x3f, sizeof f);
        f[0][1] = 0, f[0][0] = f[0][2] = 1;
        for (int i = 1; i < n; ++i) {
            if (b[i] != 1) f[i][0] = f[i-1][0];
            if (b[i] != 2) f[i][1] = f[i-1][1];
            if (b[i] != 3) f[i][2] = f[i-1][2];
            if (b[i] != 1) f[i][0] = min(f[i][0], min(f[i][1], f[i][2]) + 1);
            if (b[i] != 2) f[i][1] = min(f[i][1], min(f[i][0], f[i][2]) + 1);
            if (b[i] != 3) f[i][2] = min(f[i][2], min(f[i][0], f[i][1]) + 1);
        }
        return *min_element(f[n - 1], f[n - 1] + 3);
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(n)}$