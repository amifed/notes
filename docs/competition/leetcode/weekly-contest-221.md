# [第 221 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-221/)

## A. [判断字符串的两半是否相似](https://leetcode-cn.com/problems/determine-if-string-halves-are-alike/)

### 解法一：计数

前一半字符串和后一半字符串分别计数

#### 参考代码

```python
class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        n = len(s)
        p = 'aeiouAEIOU'
        return sum(s[i] in p for i in range(n // 2)) == sum(s[i] in p for i in range(n // 2, n))
```

## B. [吃苹果的最大数目](https://leetcode-cn.com/problems/maximum-number-of-eaten-apples/)

### 解法一：贪心 + 最小堆

使用优先队列（最小堆）记录 $\{ 过期时间, 剩余数量 \}$ ，

#### 算法步骤

- 每次从队列中拿出已经过期的和剩余数量为$0$ 的苹果
- 队列中如果还有苹果，取出苹果，将数量减一再入队
- 如果当天仍能摘苹果，将新摘的苹果入队。

#### 参考代码

```cpp
using PII = pair<int, int>;
class Solution {
public:
    int eatenApples(vector<int>& a, vector<int>& d) {
        int n = a.size();
        int ans = 0, i = 0;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.push({d[0], a[0]});
        while (!q.empty() || i < n) {
            while (!q.empty() && (q.top().first <= i || q.top().second <= 0)) q.pop(); 
            if (!q.empty()) {
                auto p = q.top(); q.pop();
                q.push({p.first, p.second - 1});
                ans++;
            }
            i++;
            if (i < n) q.push({i + d[i], a[i]});
        }
        return ans;
    }
};
```

## C. [球会落何处](https://leetcode-cn.com/problems/where-will-the-ball-fall/)

### 解法一：模拟

根据条件模拟，当前格`左上到右下`且右边的一格`左上到右下` 或 当前格`右上到左下`且左边的一格`右上到左下` 才能往下掉一格。

```cpp
class Solution {
public:
    int m, n;
    int find(vector<vector<int>> g, int j) {
        for (int i = 0; i < g.size(); ) {
            if (j + 1 < n && g[i][j] == 1 && g[i][j + 1] == 1) {
                ++i, ++j;
            } else if (j - 1 >= 0 && g[i][j] == -1 && g[i][j - 1] == -1) {
                ++i, --j;
            } else {
                return -1;
            }
        }
        return j;
    } 
    vector<int> findBall(vector<vector<int>>& g) {
        m = g.size(), n = g[0].size();
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            ans.push_back(find(g, i));
        }
        return ans;
    }
};
```



