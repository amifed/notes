const a = [1, 3, 5, 7, 9]
let l = 0,
  r = a.length - 1
while (l < r) {
  let mid = (l + r) >> 1
  if (a[mid] >= 4) r = mid
  else l = mid + 1
}
console.log(a[l])
