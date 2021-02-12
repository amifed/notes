# [ABC-190](https://atcoder.jp/contests/abc190) 题解

## [A - Very Very Primitive Game](https://atcoder.jp/contests/abc190/tasks/abc190_a)

- $C = 0$，$A > B$ Takahashi 赢;
- $C = 1$，$A ≥ B$ Takahashi 赢。

::: details 参考代码（C++）
<<< @/docs/contest/atcoder/abc190/a.cpp
:::

## [B - Magic 3](https://atcoder.jp/contests/abc190/tasks/abc190_b)

检查是否存在 $X_i < s$ 且 $Y_i > d$

::: details 参考代码（C++）
<<< @/docs/contest/atcoder/abc190/b.cpp
:::

## [C - Bowls and Dishes](https://atcoder.jp/contests/abc190/tasks/abc190_c)

每个人有两种选择（在盘子 $C$ 或 $D$ 中放一个球，枚举所有可能的选择，共 $2^K$ 种可能。

由 $1 ≤ K ≤ 16$，枚举使用二进制位运算，每一位的 $0$ 或 $1$ 代表选择盘子 $C$ 或 $D$。

::: details 参考代码（C++）
<<< @/docs/contest/atcoder/abc190/c.cpp
:::
