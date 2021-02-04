# 数学知识

## 试除法判定质数

```cpp
bool is_prime(int x) {
  if (x < 2) return 0;
  for (int i = 2; i <= x / i; ++i) 
    if (x % i == 0) return 0;
  return 1;
}
```

- 时间复杂度 $O(\sqrt n)$

> 不推荐使用 `i <= sqrt(x)` 或 `i * i <= n` 的写法，前者存在计算时间消耗，后者存在溢出的可能

## 试除法分解质因数

**$x$ 中只存在一个大于 $\sqrt x$ 的质因子 **,可使用反证法证明：

如果 $x$ 中存在两个大于 $\sqrt x$ 的质因子 $a > \sqrt x, b > \sqrt x$, 则 $a \times b > \sqrt x \times \sqrt x = x$, 一个数的质因子的乘积大于该数，不符合定义。

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

- 时间复杂度 $O(\sqrt n)$

## 朴素筛法求素数

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

调和级数：$\frac{n}{2} + \frac{n}{3} + \dots + \frac{n}{n} = n \left( \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{n} \right) $

算法可做以下优化, 只将 $2 \sim n$ 中的质数的倍数筛除即可, （埃式筛法）

```cpp
void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) {
            ps[cnt++] = i;
            for (int j = i + i; j <= n; j += i)
                vt[j] = 1;
        }
    }
}
```

- 时间复杂度 $O(n\log\log n)$

由质数定理，$1 \sim n$ 中有 $\frac{n}{\ln n}$ 个质数，即

> 朴素筛法会出现重复筛除同一个数的情况，比如 $2$ 和 $3$ 都会筛除 $6$, n的值越大,重复的情况就越多

## 线性筛法求素数 

循环中任何一个数 i **只会被它的最小质因子筛掉**，每个数都会有一个最小质因子，因此每个数都只会被筛一次。

内层 for 循环是从头开始遍历质数表中的质数，无论 i 为质数或合数，都会枚举到它的最小质因子

1. $i \ \% \ ps[j] = 0$ 时，$ps[j]$ 为 $i$ 的最小质因子，$ps[j]$ 一定是 $ps[j] \times i$ 的最小质因子；
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

- 时间复杂度 $O(n \log \log n)$

## 试除法求所有约数

```cpp
vector<int> getDivisors(int x) {
    vector<int> ans;
    for (int i = 1; i <= x / i; ++i) {
        if (x % i == 0) {
            ans.push_back(i);
            if (i != x / i) ans.push_back(x / i); //特判, x != i * i
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}
```

## 约数个数与约数之和

### 约数定理

对于一个大于 $1$ 的正整数 $n$，可以[分解质因数](https://baike.baidu.com/item/分解质因数)：
$$
n=\prod_{i=1}^{k} p_{i}^{a_{i}}=p_{1}^{a_{1}} \cdot p_{2}^{a_{2}} \cdots p_{k}^{a_{k}}
$$
则 $n$ 的[正约数](https://baike.baidu.com/item/正约数/882466)的个数就是：
$$
f(n)=\prod_{i=1}^{k}\left(a_{i}+1\right)=\left(a_{1}+1\right)\left(a_{2}+1\right) \cdots\left(a_{k}+1\right)
$$
其中 $a_1, a_2, a_3, \dots, a_k$ 是 $p_1, p_2, p_3, \dots, p_k$ 的指数。

那么 $n$ 的 $\left(a_{1}+1\right)\left(a_{2}+1\right) \cdots\left(a_{k}+1\right)$ 个正约数的和为：
$$
f(n) = (p_1^0+p_1^1+p_1^2+\dots+p_1^{a_1})(p_2^0+p_2^1+p_2^2+\dots+p_2^{a_2})\cdots(p_k^0+p_k^1+p_k^2+\dots +p_k^{a_k}）
$$

### 定理证明

证明：

若 $n$ 可以分解质因数：$n=p_1^{a_1} * p_2^{a_2} * \cdots * p_k^{a_k}$, 

可知， $p_1^{a_1}$ 的约数有：$p_1^0 ,p_1^1,p_1^2,\dots,p_1^{a_1}$ 

$\ldots$

同理可知，$p_k^{a_k}$ 的约数有：$p_k^0,p_k^1,p_k^2,\dots,p_k^{a_k}$;

实际上 $n$ 的约数是在 $p_0^{a_0},p_1^{a_1},p_2^{a_2},\ldots,p_k^{a_k}$ 每一个的约数中分别挑一个相乘得来，

可知共有 $\left(a_{1}+1\right)\left(a_{2}+1\right) \cdots\left(a_{k}+1\right)$ 种挑法，即约数个数。

有 [乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86) 可知它们的和为

$f(n) = (p_1^0+p_1^1+p_1^2+\dots+p_1^{a_1})(p_2^0+p_2^1+p_2^2+\dots+p_2^{a_2})\cdots(p_k^0+p_k^1+p_k^2+\dots +p_k^{a_k}）$

### 例题

$180 = 2^2 * 3^2 * 5^1$

约数个数：$(2 + 1)(2 + 1)(1 + 1) = 18$

约数和：$(1 + 2 + 4)(1 + 3 + 9)(1 + 5) = 546$

### 约数个数

```cpp
int dividedCount(int x) {
    int ans = 1;
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, ++s;
            ans *= (s + 1);
        }
    }
    if (x > 1) ans *= 2;
    return ans;
}
```

### 约数之和

```cpp
int dividedSum(int x) {
    LL ans = 1;
    for (int i = 2; i <= x / i; ++i) {
        LL t = 1;
        while (x % i == 0) x /= i, t = (t * i + 1) % MOD;
        ans = ans * t % MOD;
    }
    if (x > 1) ans = ans * (x + 1) % MOD;
    return ans;
}
```

其中 $t = t * p + 1$

$t = 1$

$t = p + 1$

$t = p^2 + p + 1$

$\ldots$

$t = p^b + p^{b-1} + \ldots + 1$

## 最大公约数

如果存在一个整数 $k$，使得 $a = kd$，则称 $d$ 整除 $a$，记做 $d \mid a$，称 $a$ 是 $d$ 的倍数，如果 $d > 0$，称 $d$ 是 $a$ 的约数。特别地，任何整数都整除 $0$。

一组数的公约数，是指同时是这组数中每一个数的约数的数。而最大公约数，则是指所有公约数里面最大的一个。

### 欧几里得算法（辗转相除法）

#### 算法思想

如果我们已知两个数 $a$ 和 $b$，如何求出二者的最大公约数呢？

不妨设 $a > b$

我们发现如果 $b$ 是 $a$ 的约数，那么 $b$ 就是二者的最大公约数。下面讨论不能整除的情况，即 $a = b \times q + r$ ，其中 $r < b$。

我们通过证明可以得到 $\gcd(a, b) = \gcd(b, a\mod b)$，过程如下：

设 $a = bk + c$，显然有 $c = a \mod b$，设 $d \mid a, \ d \mid b$，则 $c = a - bk,\ \frac{c}{d} = \frac{a}{d} - \frac{b}{d}k$，由右边的式子可知 $\frac{c}{d}$ 为整数，即 $d \mid c$ 所以对于 $a, b$ 的公约数，它也会是 $a \mod b$ 的公约数。

反过来证明

设 $d \mid b,\ d \mid (a \mod b)$，可得 $a = bk + a \mod b, \ \frac{a}{d} = \frac{a \mod b}{d} +   \frac{b}{d}k$，由右边的式子可知 $\frac{c}{d}$ 为整数，即 $d \mid a$，所以 $b,\ a \mod b$ 的公约数也是 $a, \ b$ 的公约数。

既然两式公约数都是相同的，那么最大公约数也会相同。

所以得到式子 $\gcd(a, b) = \gcd(b, a\mod b)$

既然得到了 $\gcd(a, b) = \gcd(b, r)$，这里两个数的大小是不会增大的，那么我们也就得到了关于两个数的最大公约数的一个递归求法。

#### 参考代码

```cpp
int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}
```

#### 时间复杂度 $O(\log n)$

当我们求 $\gcd(a, b)$ 的时候，会遇到两种情况：

- $a < b$ ，这时候 $\gcd(a, b) = \gcd(b, a)$；
- $a > b$ ，这时候 $\gcd(a, b) = \gcd(b, a \mod b)$，而对 $a$ 取模会让 $a$ 至少折半。这意味着这一过程最多发生 $O(\log n)$ 次。

第一种情况发生后一定会发生第二种情况，因此第一种情况的发生次数一定 **不多于** 第二种情况的发生次数。

从而我们最多递归 $O(\log n)$ 次就可以得出结果。

## 欧拉函数

1 ~ N 中与 N 互质的数的个数被称为欧拉函数，记为 $\varphi(N)$。

若在算数基本定理中，$N=p_1^{a_1}p_2^{a_2} \cdots p_m^{a_m}$，则：
$$
\varphi(N) = N \times \frac{p_1 - 1}{p_1} \times \frac{p_2 - 1}{p_2} \times \cdots \times \frac{p_m - 1}{p_m}
$$

```cpp
int euler_phi(int x) {
	int ans = x;
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans; 
}
```

##  快速幂

- 递归

```cpp
int fastPow(int a, int b, int p) {
    if (b == 0) return 1 % p;
    int tmp = fastPow(a, b >> 1, p) % p;
    if (b & 1) return 1LL * tmp * tmp % p * a % p;
    return 1LL * tmp * tmp % p;
}
```

- 迭代

```cpp
int fastPow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1LL * ans * a % p;
        a = 1LL * a * a % p;
        b >>= 1;
    }
    return ans;
}
```

