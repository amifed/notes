# Trie 树（前缀树）


```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 7;
// 0 为根结点也是空结点， son[][] 存储每个结点的字结点， cnt[] 存储以结点结尾的单词数量
int son[N][26], cnt[N], idx;
char str[N];

// 插入
void insert(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int q = str[i] - 'a';
        if (!son[p][q]) son[p][q] = ++idx; // 0 为根结点
        p = son[p][q];
    }
    ++cnt[p];
}

// 查询
int query(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int q = str[i] - 'a';
        if (!son[p][q]) return 0;
        p = son[p][q];
    }
    return cnt[p];
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char op[2];
        scanf("%s%s", op, str);
        if (op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
    return 0;
}
```

题目: 
- [LeetCode 208. 实现 Trie (前缀树)](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
- [LeetCode 421.数组中两个数的最大异或值](https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/)
