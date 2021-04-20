# 字符串

## KMP 模式匹配

### KMP 算法 $next$ 数组的求法

1. 初始化 $next[1]=j=0$，假设 $next[1\sim i-1]$ 已求出，求 $next[i]$。
2. 不断尝试扩展匹配长度 $j$，如果扩展失败（下一个字符不相等），另 $j=next[j]$，直至 $j$ 为 $0$（应该重新从头开始匹配）。
3. 如果能扩展成功，匹配长度 $j$ 就增加 $1$。$next[i]=j$。

```cpp
ne[1] = 0;
for (int i = 2, j = 0; i <= n; ++i) {
    while (j && p[i] != p[j + 1]) j = ne[j];
    if (p[i] == p[j + 1]) ++j;
    ne[i] = j;
}
```

### KMP 算法匹配过程

```cpp
for (int i = 1, j = 0; i <= m; ++i) {
    while (j && s[i] == p[j + 1]) j = ne[j];
    if (s[i] == p[j + 1]) ++j;
    if (j == n) {
        cout << i - n << endl;
        j = ne[j];
    }
}
```

> 参考文章：《算法进阶指南》、[KMP 算法详解](https://yuhi.xyz/post/KMP-%E7%AE%97%E6%B3%95%E8%AF%A6%E8%A7%A3/#top)
