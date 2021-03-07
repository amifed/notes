# 质数

## 试除法判定质数

```cpp
bool is_prime(int x) {
  if (x < 2) return 0;
  for (int i = 2; i <= x / i; ++i)
    if (x % i == 0) return 0;
  return 1;
}
```

- 时间复杂度 $\mathcal{O(\sqrt{n})}$

> 不推荐使用 `i <= sqrt(x)` 或 `i * i <= n` 的写法，前者存在计算时间消耗，后者存在溢出的可能

## 试除法分解质因数

**$x$ 中只存在一个大于 $\sqrt x$ 的质因子**, 可使用反证法证明：

如果 $x$ 中存在两个大于 $\sqrt x$ 的质因子 $a > \sqrt{x},b>\sqrt{x}$, 则 $a\times{b}> \sqrt{x}\times\sqrt{x}=x$, 一个数的质因子的乘积大于该数，不符合定义。

```cpp
void divide(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, ++s;
            printf("%d %d\n", i, s);
        }
    }
    if (x > 1) printf("%d %d\n", x, 1); // 判断是否存在大于 sqrt(x) 的质因子
    printf("\n");
}
```

> 从 2 开始除，得到的能够整除的数一定是质数

- 时间复杂度 $\mathcal{O(\sqrt n)}$

## 朴素筛法求质数

从 $2 \sim n$ 枚举，将其倍数删除，剩下的数就是质数

```cpp
const int N = 1e6 + 7;
int ps[N], cnt;
bool vt[N];

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) ps[cnt++] = i;
        for (int j = i + i; j <= n; j += i) vt[j] = 1;
    }
}
```

- 时间复杂度 $O(n\log n)$

调和级数：$\frac{n}{2} + \frac{n}{3} + \dots + \frac{n}{n} = n \left( \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{n} \right)$

## 埃式筛法求质数

考虑这样一个事实：如果 $x$ 是质数，那么大于 $x$ 的 $x$ 的倍数 $2x,3x,\ldots$ 一定不是质数。

朴素筛法可做以下优化, 只将 $2 \sim n$ 中的质数的倍数筛除即可。

这里还可以继续优化，对于一个质数 $x$，如果按上文说的我们从 $2x$ 开始标记其实是冗余的，应该直接从 $x\cdot x$ 开始标记，因为 $2x,3x,\ldots$ 这些数一定在 $x$ 之前就被其他数的倍数标记过了，例如 $2$ 的所有倍数，$3$ 的所有倍数等。

```cpp
void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) {
            ps[cnt++] = i;
            for (int j = i * i; j <= n; j += i) vt[j] = 1;
        }
    }
}
```

- 时间复杂度 $\mathcal O(n\log{\log{n}})$

由质数定理，$1 \sim n$ 中有 $\frac{n}{\ln n}$ 个质数，即

## 线性筛法求质数

埃氏筛其实还是存在冗余的标记操作，比如对于 $45$ 这个数，它会同时被 $3,5$ 两个数标记为合数，因此我们优化的目标是让每个合数只被标记一次，这样时间复杂度即能保证为 $\mathcal{O(n)}$。

循环中任何一个数 $i$ **只会被它的最小质因子筛掉**，每个数都会有一个最小质因子，因此每个数都只会被筛一次。

内层 $\textit{for}$ 循环是从头开始遍历质数表中的质数，无论 $i$ 为质数或合数，都会枚举到它的最小质因子

1. $i\;\%\;ps[j] = 0$ 时，$ps[j]$ 为 $i$ 的最小质因子，$ps[j]$ 一定是 $ps[j] \times i$ 的最小质因子；
2. $i \ \% \ ps[j] \ne 0$ 时，$ps[j]$ 一定小于 $i$ 的所有质因子，$ps[j]$ 也一定是 $ps[j] \times i$ 的最小质因子。

```cpp
const int N = 1e6 + 7;
int ps[N], cnt;
bool vt[N];

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) ps[cnt++] = i;
        for (int j = 0; ps[j] <= n / i; ++j) { //从头开始遍历质数表中的质数
          vt[ps[j] * i] = 1;
          if (i % ps[j] == 0) break;
        }
    }
}
```

- 时间复杂度 $\mathcal{O(n)}$
