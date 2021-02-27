# 数据结构

## 单链表

使用一维数组表示单链表，其中 $N$ 为结点个数，$head$ 表示头指针，$e$ 存储结点的值，$ne$ 存储结点的下一个结点的下标，idx 为当前结点的位置。

```cpp
const int N = 5;

int head, e[N], ne[N], idx;
// 初始化
void init() {
  head = -1, idx = 0;
}
// 头插法插入单链表
void insert(int a) {
  e[idx] = a, ne[idx] = head, head = idx++;
}
// 在第 k 个位置后插入单链表
void insert(int k, int a) {
  e[idx] = a, ne[idx] = ne[k], ne[k] = idx++;
}
// 删除第 k 个结点
void remove(int k) {
	ne[k] = ne[ne[k]];
}
void output() {
    for (int p = head; p != -1; p = ne[p])
        cout << e[p];
}
```

例如：将序列 $[1, 2, 3]$ 的存储为单链表， $head = 2,  e = [3, 5, 1],  ne = [-1, 0, 1];$ 得到头插法的单链表。3 -> 2 -> 1。

## 双链表

```cpp
const int N = 1e5 + 7;

int m;
int e[N], l[N], r[N], idx;
int init() {
    r[0] = 1, l[1] = 0;
    idx = 2;
}
void add(int k, int x) {
    e[idx] = x;
    l[idx] = k, r[idx] = r[k];
    l[r[k]] = idx, r[k] = idx++;
}
void remove(int k) {
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}
```

## 栈

```cpp
const int N = 1e5 + 7;
int stk[N], tt; // 栈顶指针
// 初始化
tt = -1;
// 入栈
stk[++tt] = x;
// 出栈
--tt;
// 栈顶元素
stk[tt];
// 栈空
if (tt == -1) return true;
```

## 队列

### 普通队列

```cpp
const int N = 1e5 + 7;
int q[N], hh, tt; // 队头指针(出队)，队尾指针（入队）
// 初始化
hh = 0, tt = -1;
// 入队
q[++tt] = x;
// 出队
++hh;
// 队头
q[hh];
// 队不空
if (hh <= tt) return true;
// 队满
if (tt == N) return true;
```

> 普通队列存在一种“假溢出”现象，即尾指针指向数组末尾时，队列不一定满

### 循环队列

```cpp
const int N = 1e5 + 7;
int q[N], hh, tt;
// 初始化
hh = tt = 0;
// 入队
q[tt] = x;
tt = (tt + 1) % N;
// 出队
hh = (hh + 1) % N;
// 队头
q[hh];
// 队空
if (hh == tt) return true;
// 队满
if ((hh + 1) % N == tt) return true;
```

## 单调栈

```cpp
const int N = 1e5 + 7;
int stk[N], tt = -1;
for (int i = 0; i < n; i++) {
  while (tt != -1 && check(tt, i)) --tt;
  stk[++tt] = i;
}
```

## 单调队列

```cpp
int hh = 0, tt = -1;
for (int i = 0; i < n; i ++ ) {
    while (hh <= tt && check_out(q[hh])) hh++ ;  // 判断队头是否滑出窗口
    while (hh <= tt && check(q[tt], i)) tt-- ;
    q[++tt] = i;
}
```

## KMP

```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 7, M = 1e6 + 7;
int n, m;
char p[N], s[M];
int ne[N];

int main() {
    scanf("%d%s%d%s", &n, p + 1, &m, s + 1);
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && p[i] != p[j + 1])
            j = ne[j];
        if (p[i] == p[j + 1]) ++j;
        ne[i] = j;
    }

    // KMP匹配
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j && s[i] != p[j + 1])
            j = ne[j];
        if (s[i] == p[j + 1]) ++j;
        if (j == n) {
          	// 输出匹配的起始坐标
            printf("%d ", i - n);
            j = ne[j];
        }
    }
    return 0;
}
```

## 堆

- 堆排序

```cpp
const int N = 1e5 + 7;
int n, m;
int h[N], idx;

// 向下调整
void down(int x) {
	int t = x;
  if (x * 2 <= idx && h[x * 2] < h[t]) t = x * 2;
  if (x * 2 + 1 <= idx && h[x * 2 + 1] < h[t]) t = x * 2 + 1;
  if (t != x) {
    swap(h[x], h[t]);
    down(t);
  }
}
```

- 模拟堆

## 散列表

- 开放定址法 - 线性探测

```cpp
const int N = 2e5 + 7, INF = 0x3f3f3f3f;
int h[N];

// 如果x在散列表中，返回x的下标；如果x不在散列表中，返回x应该插入的位置
int find(int x) {
  int k = (x % N + N) % N;
  while (h[k] != INF && h[x] != x)
    	if (++k == N) k = 0;
 	return k;
}

// insert
h[find(x)] = x;

// check
h[find(x)] != INF
```

- 拉链法

```cpp
const int N = 1e5 + 7;
int h[N], e[N], ne[N], idx;

void insert(int x) {
  int k = (x % N + N) % N;
  e[idx] = x, ne[idx] = h[k], h[k] = idx++;
}

bool find(int x) {
  int k = (x % N + N) % N;
  for (int i = h[k]; i != -1; i = ne[i])
    if (e[i] == x) return 1;
  return 0;
}
```

## 字符串哈希

将字符串看成 $P$ 进制的数, $P$ 的经验值是 $131$ 或 $13331$, 取这两个值的冲突概率低

小技巧：取模的数用 $2^{64}$, 这样直接用 unsigned long long 存储，溢出的结果就是取模的结果

```cpp
using ULL = unsigned long long;
const int N = 1e5 + 7, p = 131;

char s[N];
ULL h[N], p[N];

// 初始化
p[0] = 1;
for (int i = 1; i <= n; ++i) {
  p[i] = p[i - 1] * P;
  h[i] = h[i - 1] * P + s[i];
}

// 计算子串 s[l……r] 的哈希值
ULL get(int l, int r) {
  return h[r] - h[l - 1] * p[r - l + 1];
}
```

## C++ STL

- 优先队列 （堆）

  - 引用

  ```cpp
  #include <queue>
  ```

  - 常用函数

  ```cpp
  pq.top(); // 取堆顶元素
  pq.empty(); // 队列是否为空
  pq.size();
  pq.push(1);
  pq.emplace(); // 传入参数，自动构建
  pq.pop();
  ```

  - 基本数据结构的优先队列

  ```cpp
  #include <queue>
  #include <vector>

  // 默认大根堆
  priority_queue<int> pq;
  priority_queue<int, vector<int>, less<int>> pq;
  // 小根堆
  priority_queue<int, vector<int>, greater<int>> pq;
  ```

  - lambda 表达式

    - 参考代码

    ```cpp
    int A[], B[];
    auto cmp = [&](const int& a, const int& b) {
                return A[a] < B[b];
    };
    priority_queue<int, vector<int>,  decltype(cmp)> queue{cmp};
    ```

* 结构体优先队列

  - 自定义比较函数

  ```cpp
  #include <queue>
  #include <vector>
  using namespace std;
  struct node {
    int x, y;
    node (int _x, int _y): x(_x), y(_y){};
  };

  struct cmp {
    bool operator()(const node &a, const node &b) {
  		return a.x > b.x;
    }
  };
  priority_queue<int, vector<int>,  cmp> queue;
  ```

  > `>` 为小顶堆, `<` 为大顶堆

  - 运算符重载

  ```cpp
  #include <queue>
  #include <vector>
  using namespace std;

  struct node {
      int x, y;
      node(int _x, int _y) : x(_x), y(_y){};
      bool operator<(const node &a) const {
        return x < a.x;
      }
  };
  ```

  > `>` 为小顶堆, `<` 为大顶堆

* set/multiset

``` cpp
lower_bound(x) // 返回大于等于 x 的最小的数的迭代器
upper_bound(x) // 返回大于 x 的最小的数的迭代器
```

- bitset

```cpp
bitset<1024> bs;
    ~, &, |, ^
    >>, <<
    ==, !=
    []

    count()  返回有多少个1

    any()  判断是否至少有一个1
    none()  判断是否全为0

    set()  把所有位置成1
    set(k, v)  将第k位变成v
    reset()  把所有位变成0
    flip()  等价于~
    flip(k) 把第k位取反
```
