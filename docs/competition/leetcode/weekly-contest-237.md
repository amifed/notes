# [第 237 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-237/)

::: details 个人成绩
$RANK: 1462 / 4576$

$SCORE: 7$

\$TIME: 0:04:54
:::

## 1.[判断句子是否为全字母句](https://leetcode-cn.com/problems/check-if-the-sentence-is-pangram/)

求单词数量

```js
/**
 * @param {string} sentence
 * @return {boolean}
 */
var checkIfPangram = function(sentence) {
  return new Set(sentence).size == 26
}
```

- 时间复杂度 $\mathcal{O(n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 2.[雪糕的最大数量](https://leetcode-cn.com/problems/maximum-ice-cream-bars/)

排序 + 贪心

```cpp
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        for (int i = 0; i < costs.size(); ++i) {
            if (coins >= costs[i]) coins -= costs[i];
            else return i;
        }
        return costs.size();
    }
};
```

- 时间复杂度 $\mathcal{O(n\log n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 3.[单线程 CPU](https://leetcode-cn.com/problems/single-threaded-cpu/)

排序 + 优先队列，每次执行一个任务，执行完成后保证结束时间前的任务全部入队；

```cpp
using ll = long long;
using pii = pair<int, int>;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        const int n = tasks.size();
        for (int i = 0; i < n; ++i) tasks[i].push_back(i);
        sort(tasks.begin(), tasks.end());
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        ll sum = 0;
        vector<int> ans;
        for (int i = 0, idx = 0; i < n; ++i) {
            if (pq.empty()) sum = max(sum, (ll)tasks[idx][0]);
            for (;idx < n && tasks[idx][0] <= sum; ++idx) pq.push({tasks[idx][1], tasks[idx][2]});
            auto p = pq.top(); pq.pop();
            sum += p.first;
            ans.push_back(p.second);
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(n\log n)}$;
- 空间复杂度 $\mathcal{O(n)}$;

## 4.[所有数对按位与结果的异或和](https://leetcode-cn.com/problems/find-xor-sum-of-all-pairs-bitwise-and/)

### 法一：逐位运算

$\oplus_{0<i<m,0<j<n} arr1[i]\;\&\;arr2[j]$

对于答案的二进制的第 $k$ 位，$arr1[i]\;\&\;arr2[j]=1$ 当前仅当 $arr1[i]$ 和 $arr2[j]$ 的二进制表示的第 $k$ 位均为 $1$，否则为 $0$。
当对所有的 $arr1[i]\;\&\;arr2[j]$ 求异或时，相当于对若干个 $1$ 和若干个 $0$ 求异或。根据异或的性质，如果有奇数个 $1$ 异或，结果为 $1$ ，否则为 $0$。

故，只要求出数组 $\textit{arr}_1$ 中二进制表示第 $k$ 位为 $1$ 的元素个数 $\textit{cnt}_1[k]$，以及数组 $\textit{arr}_2$ 中二进制表示第 $k$ 位为 $1$ 的元素个数 $\textit{cnt}_2[k]$，那么就会有 $\textit{cnt}_1[k] \times \textit{cnt}_2[k]$个 $1$ 进行异或运算，这样就确定了答案的第 $k$ 位。

```cpp
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        const int m = arr1.size(), n = arr2.size();
        int ans = 0;
        for (int i = 30; i >= 0; --i) {
            int cnt1 = 0;
            for (int &x: arr1) {
                if (x >> i & 1) ++cnt1;
            }
            int cnt2 = 0;
            for (int &x: arr2) {
                if (x >> i & 1) ++cnt2;
            }
            if (cnt1 & 1 && cnt2 & 1) ans |= 1 << i;
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O((m+n)\log C)}$，C 为数组中元素范围
- 空间复杂度 $\mathcal{O(1)}$

### 法二：推导

- 答案的二进制表示第 $k$ 位为 $1$；
- $cnt_1[k]$ 为奇数且 $cnt_2[k]$ 为奇数
- $arr_1$ 中二进制表示第 $k$ 位异或和为 $1$ 且 $arr_2$ 中二进制表示第 $k$ 位异或和为 $1$
- $arr_1$ 中二进制表示第 $k$ 位异或和 $\land$ $arr_2$ 中二进制表示第 $k$ 位异或和 $=1$
- 答案为 $arr_1$ 中元素异或和 $\land$ $arr_2$ 中元素异或和

```cpp
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int a1 = 0, a2 = 0;
        for (int &x: arr1) a1 ^= x;
        for (int &x: arr2) a2 ^= x;
        return a1 & a2;
    }
};
```

- 时间复杂度 $\mathcal{O(m+n)}$
- 空间复杂度 $\mathcal{O(1)}$
