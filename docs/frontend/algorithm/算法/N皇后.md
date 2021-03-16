# [LeetCode 51. N 皇后](https://leetcode-cn.com/problems/n-queens/)

## 回溯

```js
/**
 * @param {number} n
 * @return {string[][]}
 */
var solveNQueens = function(n) {
  const ans = [];
  const col = new Array(n).fill(false),
    deg = new Array(n * 2).fill(false),
    udeg = new Array(n * 2).fill(false),
    tmp = new Array(n).fill(0).map(() => new Array(n).fill("."));

  const dfs = (r) => {
    if (r >= n) {
      ans.push(tmp.map((t) => t.join("")));
      return;
    }
    for (let i = 0; i < n; ++i) {
      if (!col[i] && !deg[r + i] && !udeg[r - i + n]) {
        col[i] = deg[r + i] = udeg[r - i + n] = true;
        tmp[r][i] = "Q";
        dfs(r + 1);
        tmp[r][i] = ".";
        col[i] = deg[r + i] = udeg[r - i + n] = false;
      }
    }
  };

  dfs(0);
  return ans;
};
```
