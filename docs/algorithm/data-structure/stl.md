# C++ STL 常用函数

## priority_queue

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

  ```cpp
  int A[], B[];
  auto cmp = [&](const int& a, const int& b) {
              return A[a] < B[b];
  };
  priority_queue<int, vector<int>,  decltype(cmp)> queue{cmp};
  ```

- 结构体优先队列

  - 自定义比较函数

  ```cpp
  #include <queue>
  #include <vector>
  using namespace std;
  using PII = pair<int, int>;
  struct cmp {
    bool operator()(const PII &a, const PII &b) {
  		return a.first > b.first;
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

## deque

deque 是 double-ended queue 的缩写，又称双端队列容器。

- deque 容器擅长在序列尾部添加或删除元素（时间复杂度为O(1)），而不擅长在序列中间添加或删除元素。
- deque 容器可以根据需要修改自身的容量和大小。

```cpp
#include <deque>
using namespace std;
deque<int> dq;
dq.push_back()	//在容器现有元素的尾部添加一个元素
dq.pop_back()	//移除容器尾部的一个元素。
dq.push_front()	//在容器现有元素的头部添加一个元素
dq.pop_front()	//移除容器头部的一个元素。
dq.emplace_bacK() //在容器尾部生成一个元素
dq.emplace_front() //在容器头部生成一个元素
```

## list

双向链表容器，即该容器的底层是以双向链表的形式实现的。

```cpp
#include <list>
using namespace std;
list<int> lt;
lt.size() //元素个数
lt.front() // 返回第一个元素的引用
lt.back()	//返回最后一个元素的引用
lt.push_front()	//在容器头部插入一个元素
lt.pop_front()	//删除容器头部的一个元素
lt.push_back()	//在容器尾部插入一个元素
lt.pop_back()	//删除容器尾部的一个元素
```

## bitset

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

## lower_bound / upper_bound

``` cpp
lower_bound(x) // 返回大于等于 x 的左边界的迭代器
upper_bound(x) // 返回大于 x 的左边界的迭代器
```