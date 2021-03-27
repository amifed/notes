# 排序

## 快速排序

这种写法只能保证 `q[l...j] <= x`、`q[j+1...r] >= x`，并不能保证每次排序 x 都能放在最终位置。

```cpp
const int N = 1e5 + 7;
int n, q[N];
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}
```

> 枢轴选择中间位置的值能避免在极端情况下（数组元素全部相等）退化成 $O(n^2)$ 的时间复杂度。

另一种相同的写法，划分区间为 `q[l, i - 1]`、`q[i, r]`；

```cpp
void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int x = q[l + r + 1 >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, i - 1), quick_sort(q, i, r);
}
```

> 注意枢轴的选择为 `l + r + 1 >> 1`， 防止划分为 `[]，[l, r]`造成死循环

## 归并排序

```cpp
const int N = 1e5 + 7;
int n, q[N], tmp[N];
void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int m = l + r >> 1;
    merge_sort(q, l, m), merge_sort(q, m + 1, r);

    int k = 0, i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= m) tmp[k++] = q[i++];
    while (j <= r)tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
}
```
