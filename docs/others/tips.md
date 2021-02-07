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

- $n≤30$, 指数级别, dfs+剪枝，状态压缩dp
- $n≤100$ => $O(n3)O(n3)$，floyd，dp，高斯消元
- $n≤1000$ => $O(n2)O(n2)$，$O(n2logn)O(n2logn)$，dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford
- $n≤10000$ => $O(n∗n‾√)O(n∗n)$，块状链表、分块、莫队
- $n≤100000$ => $O(nlogn)O(nlogn)$ => 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、spfa、求凸包、求半平面交、二分、CDQ分治、整体二分
- $n≤1000000$ => $O(n)O(n)$, 以及常数较小的 $O(nlogn)O(nlogn)$ 算法 => 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机$，$- 常数比较小的 $O(nlogn)O(nlogn)$ 的做法：sort、树状数组、heap、dijkstra、spfa
- $n≤10000000$ => $O(n)O(n)$，双指针扫描、kmp、AC自动机、线性筛素数
- $n≤10^9$ => $O(n‾√)O(n)$，判断质数
- $n≤10^18$ => $O(logn)O(logn)$，最大公约数，快速幂
- $n≤10^1000$ => $O((logn)2)O((logn)2)$，高精度加减乘除
- $n≤10^100000$ => $O(logk×loglogk)$，k表示位数 $O(logk×loglogk)$，k表示位数，高精度加减、FFT/NTT

