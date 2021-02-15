# 排列组合

## 排列问题

从 $n$ 个不同元素中取出 $m(m≤n)$ 个元素的所有不同排列的个数，叫做从 $n$ 个不同元素中取出 $m$ 个元素的排列数，用符号 $A_n^m$ 表示。

$A_n^m=n(n-1)(n-2)\cdots(n-m+1)=\displaystyle\frac{n!}{(n-m)!},\quad n,m\in\mathrm{N^*},m≤n$

## 组合问题

从 $n$ 个不同元素中取出 $m(m≤n)$ 个元素的所有不同组合的个数，叫做从 $n$ 个不同元素中取出 $m$ 个元素的排列数，用符号 $C_n^m$ 表示。

$C_n^m=\displaystyle\frac{A_n^m}{A_m^m}=\frac{n(n-1)(n-2)\cdots(n-m+1)}{m!}=\frac{n!}{m!(n-m)!},\quad n,m\in\mathrm{N^*},m≤n$

> 参考文章：[排列组合的一些公式及推导(非常详细易懂)](https://www.cnblogs.com/1024th/p/10623541.html)