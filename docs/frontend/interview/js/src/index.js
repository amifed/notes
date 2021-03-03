var arrangeCoins = function(n) {
  let l = 0,
    r = n;
  let ans = 0;
  while (l < r) {
    let mid = Math.floor((l + r + 1) / 2);
    if ((1 + mid) * mid <= 2 * n) {
      l = mid;
      ans = Math.max(ans, mid);
    } else r = mid - 1;
  }
  console.log(((1 + l) * l) / 2);
  return l;
};
