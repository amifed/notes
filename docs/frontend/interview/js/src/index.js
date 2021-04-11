const [n, m] = [2, 3]
const am = [0, 585, 375, 1001]
const at = [0, 936,317,185, 10001]
am.sort((a, b) => a - b)
at.sort((a, b) => a - b)
console.log(am);
console.log(at);
function bs(arr, k) {
  let l = 0, r = arr.length - 1
  while (l < r) {
    let mid = l + r + 1 >> 1
    if (arr[mid] <= k) l = mid
    else r = mid - 1
  }
  return r
}
console.log(bs(am, 587));
let ans = Number.MIN_SAFE_INTEGER
for (let d = 1; d <= 1000; ++d) {
  let im = bs(am, d)
  let it = bs(at, d)
  let sm = im + (n - im) * 2
  let st = it + (m - it) * 2
  ans = Math.max(st - sm, ans)
}
console.log(ans);