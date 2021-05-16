# [第 51 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-51/)

## 1.[将句子排序](https://leetcode-cn.com/problems/sorting-the-sentence/)

模拟

```js
/**
 * @param {string} s
 * @return {string}
 */
var sortSentence = function(s) {
  const a = s.split(' ')
  const ans = new Array(a.length)
  for (let x of a) {
    ans[x[x.length - 1] - '1'] = x.substr(0, x.length - 1)
  }
  return ans.join(' ')
}
```

- 时间复杂度 $\mathcal{O}(n)$
- 空间复杂度 $\mathcal{O}(n)$

## 2.[增长的内存泄露](https://leetcode-cn.com/problems/incremental-memory-leak/)

模拟

```cpp
class Solution {
public:
    vector<int> memLeak(int m1, int m2) {
        int m = 1;
        while (m1 >= m || m2 >= m) {
            if (m1 >= m && m2 >= m) {
                if (m1 >= m2) m1 -= m;
                else m2 -= m;
            } else if (m1 >= m) m1 -= m;
            else if (m2 >= m) m2 -=m;
            ++m;
        }
        return {m, m1, m2};
    }
};
```

- 时间复杂度 $\mathcal{O}(\sqrt{\max{(m1,m2)}})$
- 空间复杂度 $\mathcal{O}(1)$

## 3.[旋转盒子](https://leetcode-cn.com/problems/rotating-the-box/)

模拟

```cpp
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        const int m = box.size(), n = box[0].size();
        vector<vector<char>> ans(n, vector<char> (m));
        for (int i = 0; i < m; ++i) {
            int cnt = 0, pre = n - 1;
            for (int j = n - 1; j >= 0; --j) {
                if (box[i][j] == '#') ++cnt;
                else if (box[i][j] == '*') {
                    for (int k = pre; k > j; --k) {
                        if (cnt-- > 0) box[i][k] = '#';
                        else box[i][k] = '.';
                    }
                    cnt = 0, pre = j - 1;
                }
            }
            for (int k = pre; k >= 0; --k) {
                if (cnt-- > 0) box[i][k] = '#';
                else box[i][k] = '.';
            }
        }
        for (int j = 0; j < n; ++j) for (int i = 0; i < m; ++i)
            ans[j][m - i - 1] = box[i][j];

        return ans;
    }
};
```

## 4.[向下取整数对和](https://leetcode-cn.com/problems/sum-of-floored-pairs/)
