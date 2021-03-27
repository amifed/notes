# 基础算法

## 双指针

双指针通常用来优化算法的时间复杂度。

```cpp
for (int i = 0, j = 0; i < n; i++ ) {
    while (j < i && check(i, j)) j++ ;
    // 具体问题的逻辑
}
```

## 区间合并

```cpp
// 将所有存在交集的区间合并
vector<PII> merge(vector<PII> &segs) {
    vector<PII> ans;
    sort(segs.begin(), segs.end());
    int st = -INF, ed = -INF;
    for (auto &seg : segs) {
        if (ed < seg.first) {
            if (st != -INF) ans.push_back({st, ed});
            st = seg.first, ed = seg.second;
        } else
            ed = max(ed, seg.second);
    }
    if (st != -INF) ans.push_back({st, ed});
    return ans;
}
```
