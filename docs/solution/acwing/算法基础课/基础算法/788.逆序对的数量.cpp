/*
给定一个长度为n的整数数列，请你计算数列中的逆序对的数量。

逆序对的定义如下：对于数列的第 i 个和第 j 个元素，如果满足 i < j 且 a[i] >
a[j]，则其为一个逆序对；否则不是。

输入格式
第一行包含整数n，表示数列的长度。

第二行包含 n 个整数，表示整个数列。

输出格式
输出一个整数，表示逆序对的个数。

数据范围
1≤n≤100000
输入样例：
6
2 3 4 5 6 1
输出样例：
5
*/
#include <iostream>
using namespace std;

using LL = long long;
const int N = 1e5 + 7;
int n, q[N], tmp[N];

LL merge_sort(int q[], int l, int r) {
    if (l >= r) return 0;
    int m = (l + r) >> 1;
    LL ans = merge_sort(q, l, m) + merge_sort(q, m + 1, r);
    int k = 0, i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (q[i] <= q[j])
            tmp[k++] = q[i++];
        else {
            ans += m - i + 1;
            tmp[k++] = q[j++];
        }
    }
    while (i <= m)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
    return ans;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);

    printf("%lld", merge_sort(q, 0, n - 1));
    return 0;
}