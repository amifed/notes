# [LeetCode 50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)

## 递归

```js
/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function(x, n) {
  const fastPow = (x, n) => {
    if (n == 0) return 1.0;
    const t = fastPow(x, n / 2);
    if (n & 1) return t * t * x;
    return t * t;
  };
  if (n >= 0) return fastPow(x, n);
  return 1 / fastPow(x, -n);
};
```

## 迭代

```js
/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function(x, n) {
  let ans = 1;
  for (let k = Math.abs(n); k; k /= 2) {
    if (k & 1) ans *= x;
    x *= x;
  }
  return n < 0 ? 1 / ans : ans;
};
```
