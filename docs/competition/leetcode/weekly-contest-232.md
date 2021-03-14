# [第 232 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-232/)

::: details 个人成绩
$RANK: 941 / 4801$

$SCORE: 11$

$TIME: 0:52:32$
:::

## 1.[仅执行一次字符串交换能否使两个字符串相等段](https://leetcode-cn.com/problems/check-if-one-string-swap-can-make-strings-equal/)

根据题意求不同字符

<CodeSwitcher :languages="{cpp:'C++',js:'JavaScript'}">
<template v-slot:cpp>

```cpp
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> dif;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) dif.push_back(i);
        }
        if (dif.size() == 1 || dif.size() > 2) return 0;
        if (dif.size() == 0) return 1;
        return s1[dif[0]] == s2[dif[1]] && s1[dif[1]] == s2[dif[0]];
    }
};
```

</template>
<template v-slot:js>

```js
/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var areAlmostEqual = function(s1, s2) {
    let dif = [];
    for (let i = 0; i < s1.length; ++i) {
        if (s1[i] != s2[i]) dif.push(i);
    }
    if (dif.length > 2 || dif.length === 1) return false;
    if (dif.length == 0) return true;
    return s1[dif[0]] == s2[dif[1]] && s1[dif[1]] == s2[dif[0]];
};
```

</template>
</CodeSwitcher>

**复杂度分析**

- 时间复杂度 $\mathcal O(|s|)$
- 空间复杂度 $\mathcal O(1)$

## 2.[找出星型图的中心节点](https://leetcode-cn.com/problems/find-center-of-star-graph/)

统计所有节点的度

<CodeSwitcher :languages="{cpp:'C++',js:'JavaScript'}">
<template v-slot:cpp>

```cpp
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int n = edges.size();
        unordered_map<int, int> ind;
        for (auto &v: edges) {
            ++ind[v[0]], ++ind[v[1]];
        }
        for (auto &p : ind) { 
            if (p.second == n) return p.first;
        }
        return 0;
    }
};
```

</template>
<template v-slot:js>

```js
/**
 * @param {number[][]} edges
 * @return {number}
 */
var findCenter = function(edges) {
  let ind = {};
  for (let [u, v] of edges) {
    ind[u] = (ind[u] ?? 0) + 1;
    ind[v] = (ind[v] ?? 0) + 1;
  }
  for (let k in ind) {
    if (ind[k] == edges.length) {
      return k;
    }
  }
  return 0;
};
```

</template>
</CodeSwitcher>

**复杂度分析**

- 时间复杂度 $\mathcal O(N)$
- 空间复杂度 $\mathcal O(N)$

## 3.[最大平均通过率](https://leetcode-cn.com/problems/maximum-average-pass-ratio/)

大根堆保存每个班级的通过考试的学生和总学生人数，将额外的学生贪心地加到是通过率增加最多的班级；

```cpp
#define x first
#define y second
using PDI = pair<double, int>;
struct cmp {
    bool operator() (const PDI &a, const PDI &b) {
        return (a.x+1)/(a.y+1)-a.x/a.y < (b.x+1)/(b.y+1)-b.x/b.y;
    };
};
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<PDI, vector<PDI>, cmp> pq;
        for (auto &v: classes) {
            pq.emplace(v[0], v[1]);
        }
        while (extraStudents--) {
            auto p = pq.top(); pq.pop();
            pq.emplace(p.x + 1, p.y + 1);
        }
        double ans = 0;
        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            ans += p.x / p.y;
        }
        return ans / classes.size();
    }
};
```