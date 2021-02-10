#include <iostream>
using namespace std;

const int N = 107;

int t, n, k, a[N], b[N], l[N];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        k = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &l[i]);
            if (!l[i]) b[k++] = a[i];
        }
        sort(b, b + k, [](const int &x, const int &y) { return x > y; });
        k = 0;
        for (int i = 0; i < n; ++i) {
            if (l[i])
                printf("%d ", a[i]);
            else
                printf("%d ", b[k++]);
        }
        printf("\n");
    }
    return 0;
}