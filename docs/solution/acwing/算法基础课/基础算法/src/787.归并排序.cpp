#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int n, q[N], tmp[N];

void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int m = l + r >> 1;
    merge_sort(q, l, m), merge_sort(q, m + 1, r);
    int k = 0, i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (q[i] <= q[j])
            tmp[k++] = q[i++];
        else
            tmp[k++] = q[j++];
    }
    while (i <= m)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);

    merge_sort(q, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", q[i]);
    return 0;
}