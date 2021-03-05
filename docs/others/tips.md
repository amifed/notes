---
sidebar: auto
---

# 小贴士

## 数组初始化

在多个测试样例需要对静态数组进行初始化的时候，如果开较大数组且每次有较多浪费，最好不要用`memset`，较耗时；

最好手动清空，`for` 循环即可。

## 输入输出

- 用 `scanf/printf`，不要用`cin/cout`

- 使用`cout`输出换行使用 `cout << '\n';`每次使用`cout << endl;`都会刷新缓冲区

- 如果使用 `cin/cout`，添加以下代码

  ```cpp
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  ```



## [由数据范围反推算法复杂度以及算法内容（转载）](https://www.acwing.com/blog/content/32/)

一般ACM或者笔试题的时间限制是1秒或2秒。
在这种情况下，C++代码中的操作次数控制在 $10^7 \sim 10^8$ 为最佳。

下面给出在不同数据范围下，代码的时间复杂度和算法该如何选择：
- $\large n≤30$, 指数级别, dfs+剪枝，状态压缩dp
- $\large n≤100$ => $\large O(n^3)$，floyd，dp，高斯消元
- $\large n≤1000$ => $\large O(n^2)$，$\large O(n^2\log n)$，dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford
- $\large n≤10000$ => $\large O(n∗\sqrt{n})$，块状链表、分块、莫队
- $\large n≤100000$ => $\large O(n\log n)$ => 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、spfa、求凸包、求半平面交、二分、CDQ分治、整体二分
- $\large n≤1000000$ => $\large O(n)$, 以及常数较小的 $\large O(n\log n)$ 算法 => 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机$，$- 常数比较小的 $\large O(n\log n)$ 的做法：sort、树状数组、heap、dijkstra、spfa
- $\large n≤10000000$ => $\large O(n)$，双指针扫描、kmp、AC自动机、线性筛素数
- $\large n≤10^9$ => $\large O(\sqrt{n})$，判断质数
- $\large n≤10^{18}$ => $\large O(\log n)$，最大公约数，快速幂
- $\large n≤10^{1000}$ => $\large O((\log n)^2)$，高精度加减乘除
- $\large n≤10^{100000}$ => $\large O(\log k * \log \log k)$，k表示位数，高精度加减、FFT/NTT

