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
codeswi;
console.log(
  findCenter([
    [1, 2],
    [2, 3],
    [4, 2],
  ])
);
