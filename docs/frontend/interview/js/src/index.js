/**
 * @param {string} s
 * @return {string[]}
 */
var permutation = function(str) {
  let ans = [];
  const dfs = (s, k) => {
      if (k == s.length - 1) {
          ans.push(s.join(''));
          return;
      }
      let st = new Set();
      for (let i = k; i < s.length; ++i) {
          if (st.has(s[i])) continue;
          st.add(s[i]);
          [s[k], s[i]] = [s[i], s[k]];
          dfs(s, k+1);
          [s[i], s[k]] = [s[k], s[i]];
      }
  }
  dfs([...str], 0);
  return ans;
};
console.log(permutation("abc"));