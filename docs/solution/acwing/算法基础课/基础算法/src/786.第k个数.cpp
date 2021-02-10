#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int n, k, q[N];

int kth_smaller(int q[], int l, int r, int k) {
    if (l == r) return q[l];
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do
            i++;
        while (q[i] < x);
        do
            j--;
        while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    int s1 = j - l + 1;
    if (s1 >= k)
        return kth_smaller(q, l, j, k);
    else
        return kth_smaller(q, j + 1, r, k - s1);
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    printf("%d", kth_smaller(q, 0, n - 1, k));
    return 0;
}