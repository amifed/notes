# Leetcode 第42场双周赛题解

## A. [无法吃午餐的学生数量](https://leetcode-cn.com/problems/number-of-students-unable-to-eat-lunch/)

### 解法一：队列模拟

根据题意使用队列模拟，直到某一轮中所有学生都不喜欢栈顶三明治为止。

```cpp
class Solution {
public:
    int countStudents(vector<int>& a, vector<int>& b) {
        queue<int> q;
        for (auto &x : a) q.push(x);
        for (auto &x : b) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                int p = q.front(); q.pop();
                if (p != x) q.push(p);
                else break;
            }
            if (q.size() == sz) return sz;
        }
        return 0;
    }
};
```

### 解法二：栈模拟

由题意可知，当存在学生喜欢这个栈顶的三明治时，该学生一定会拿到这个三明治，所以直接在统计人数。当栈顶的三明治喜欢的学生人数为 $0$ 时，终止即可。

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> stk;
        for (int i = sandwiches.size() - 1; i >= 0; --i) {
            stk.push(sandwiches[i]);
        }
        int p[2] = {0};
        for (auto &x : students) ++p[x];
        while (!stk.empty() && p[stk.top()]) {
            --p[stk.top()];
            stk.pop();
        }
        return stk.size();
    }
};
```

## B. [平均等待时间](https://leetcode-cn.com/problems/average-waiting-time/)

### 解法一：模拟

记录厨师做菜结束的时间，当一位客户到达时，分两种情况：

- 厨师不空闲，$\text{等待时间} = \text{厨师做完前面的菜的时间} + \text{做自己的菜需要的时间}$
- 厨师空闲，$\text{等待时间} = \text{做自己的菜需要的时间}$

```cpp
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int n = customers.size();
        int e = 0;
        double ans = 0;
        for (auto &v : customers) {
            if (v[0] > e) {
                ans += v[1];
                e = v[0] + v[1];
            } else {
                e += v[1];
                ans += e - v[0];
            }
        }
        return ans / n;
    }
};
```

**简化**

```cpp
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int e = 0;
        double ans = 0;
        for (auto &v : customers) {
            e = max(e, v[0]);
            e += v[1];
            ans += e - v[0];
        }
        return ans / (double)customers.size();
    }
};
```

## C. [修改后的最大二进制字符串](https://leetcode-cn.com/problems/maximum-binary-string-after-change/)

### 解法一：贪心

通过 `10` -> `01` 可以将所有的`1` 移到数字末尾；通过 `00` -> `10` 可以将 `0000...0000`这样的全零串变为`1111...1110`。

通过贪心的思想，先使用第一种操作将所有的不在开头连续的 `1` 移到末尾，使字符串变为 `11...1100...0011...11` 的形式，然后再用第二种操作将中间的全零串变为`11...1110` ，这样操作下去最终字符串最多只包含一个`1`（除初始全为`1`的情况），并且唯一的 `0`的位置要尽量靠后，因此

```cpp
class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = binary.size();
        int f = 0;
        while (binary[f] == '1' && f < n) ++f;
        if (f == n) return binary;
        int r = 0;
        for (int i = f; i < n; ++i) r += (binary[i] == '1');
        string ans(n - r - 1, '1');
        ans.push_back('0');
        ans += string(r, '1');
        return ans;
    }
};
```

### D. [得到连续 K 个 1 的最少相邻交换次数](https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/)

