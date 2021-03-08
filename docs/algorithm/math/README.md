# 数学知识

- [质数](./prime.md)
- [约数](./factor.md)
- [快速幂](./power.md)
- [排列组合](./permutation_combination.md)

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
