# 并查集

```js
class UnionFind {
  constructor(n) {
    this.p = new Array(n);
    this.cnt = n;
    for (let i = 0; i < n; ++i) this.p[i] = i;
  }
  find(x) {
    return x !== this.p[x] ? (this.p[x] = this.find(this.p[x])) : this.p[x];
  }
  unite(x, y) {
    x = this.find(x);
    y = this.find(y);
    if (x == y) {
      return 0;
    }
    this.p[x] = y;
    --this.cnt;
    return 1;
  }
}
```
