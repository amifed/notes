/**
 * @param {number} n
 * @return {string[][]}
 */
var solveNQueens = function(n) {
  const ans = [];
  const row = new Array(n).fill(false);
  (col = new Array(n).fill(false)),
    (deg = new Array(n * 2).fill(false)),
    (udeg = new Array(n * 2).fill(false)),
    (tmp = new Array(n).fill(0).map(() => new Array(n).fill(0)));

  const dfs = (r, c) => {
    if (c >= n) {
      ++r, (c = 0);
    }
    if (r >= n) {
      ans.push(tmp.map((t) => t.join("")));
      return;
    }
    tmp[r][c] = ".";
    dfs(r, c + 1);

    if (!row[r] && !col[c] && !deg[r + c] && !udeg[r - c + n]) {
      row[r] = col[c] = deg[r + c] = udeg[r - c + n] = true;
      tmp[r][c] = "Q";
      dfs(r, c + 1);
      tmp[r][c] = ".";
      row[r] = col[c] = deg[r + c] = udeg[r - c + n] = false;
    }
  };

  dfs(0, 0);
  return ans;
};

solveNQueens(4);
