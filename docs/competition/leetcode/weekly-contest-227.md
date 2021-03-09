# [第 227 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-227/)

::: details 个人成绩
$AC: 1,2,3$

$RANK: 318 / 3545$

$TIME: 0:36:42$
:::

## 1. [检查数组是否经排序和轮转得到](https://leetcode-cn.com/problems/check-if-array-is-sorted-and-rotated/)

双重循环模拟

```cpp
class Solution {
public:
    bool check(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            int k = 0;
            for (int j = i; k < n - 1; ++k, j = (j + 1) % n) {
                if (a[j] > a[(j + 1) % n]) break;
            }
            if (k == n - 1) return 1;
        }
        return 0;
    }
};
```

- 时间复杂度 $O(n^2)$
- 空间复杂度 $O(1)$

## 2. [移除石子的最大得分](https://leetcode-cn.com/problems/maximum-score-from-removing-stones/)

贪心，每次取最大的两个值

### 优先队列

```cpp
class Solution {
public:
    int maximumScore(int a, int b, int c) {
        priority_queue<int> pq();
        pq.push(a);
        pq.push(b);
        pq.push(c);
        int ans = 0;
        while (pq.size() > 1) {
            int x = pq.top(); pq.pop();
            int y = pq.top(); pq.pop();
            --x, --y;
            if (x) pq.push(x);
            if (y) pq.push(y);
            ++ans;
        }
        return ans;
    }
};
```

### 数学

如果两个堆的和小于另一个堆，那么第三个堆永远不可能为空；否则三个堆都尽可能的抵消

```cpp
class Solution {
public:
    int maximumScore(int a, int b, int c) {
        vector<int> v{a,b,c};
        sort(v.begin(),v.end());
        if(v[0]+v[1]<v[2]) return v[0]+v[1];
        return (v[0]+v[1]+v[2])/2;
    }
};
```

## 3. [构造字典序最大的合并字符串](https://leetcode-cn.com/problems/largest-merge-of-two-strings/)

字符串比较，每次选择较大的字符加入结果字符串，当两字符相等时比较后面的第一个不相等字符，选择较大的加入结果字符串。

```cpp
class Solution {
public:
    string largestMerge(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        int i = 0, j = 0;
        string ans;
        while (i < m && j < n) {
            if (s1[i] > s2[j]) ans += s1[i++];
            else if (s1[i] < s2[j]) ans += s2[j++];
            else {
                int k = 0;
                while (i + k < m && j + k < n && s1[i + k] == s2[j + k]) ++k;
                if (i + k < m && j + k < n) {
                    ans += s1[i + k] > s2[j + k] ? s1[i++] : s2[j++];
                } else if (i + k < m) {
                    ans += s1[i++];
                } else ans += s2[j++];
            }
        }
        while (i < m) ans += s1[i++];
        while (j < n) ans += s2[j++];
        return ans;
    }
};
```

### 另一种写法

```cpp
class Solution {
public:
    string largestMerge(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        int i = 0, j = 0;
        string ans;
        while (i < m && j < n) {
            if (s1.substr(i) > s2.substr(j)) ans += s1[i++];
            else ans += s2[j++];
        }
        while (i < m) ans += s1[i++];
        while (j < n) ans += s2[j++];
        return ans;
    }
};
```

> 代码来自[@wifiii](https://leetcode-cn.com/u/wifiii/)

## 4. [最接近目标值的子序列和](https://leetcode-cn.com/problems/closest-subsequence-sum/)

### 分治

根据数据范围，如果直接枚举子序列，时间复杂度为 $2^n$，题目最大 $n=40$ ，数据量过大；

就是将数组分成 $\lfloor\dfrac{n}{2}\rfloor$ 和 $\lceil\dfrac{n}{2}\rceil$两部分，然后对每个部分求出所有子集的和后再排序，这样就可以用双指针解决两个有序数组之和问题。

```cpp
using LL = long long;
class Solution {
public:
    vector<int> make(vector<int> a) {
        int n = a.size();
        vector<int> ans(1 << n);
        for (int x = 0; x < 1 << n; ++x) {
            for (int i = 0; i < n; ++i) {
                if (x >> i & 1) ans[x] += a[i];
            }
        }
        return ans;
    }
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        vector<int> l = make({nums.begin(), nums.begin() + n / 2});
        vector<int> r = make({nums.begin() + n / 2, nums.end()});
        sort(l.begin(), l.end());
        sort(r.begin(), r.end());
        int ans = 0x3f3f3f3f, i = 0, j = r.size() - 1;
        while (i < l.size() && j >=0) {
            int t = l[i] + r[j];
            ans = min(ans, abs(t - goal));
            if (t < goal) ++i;
            else if (t > goal) --j;
            else return 0;
        }
        return ans;
    }
};
```