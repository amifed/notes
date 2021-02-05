#include <iostream>
using namespace std;

const int N = 1e5 + 7;

int n, m, q[N], s[N];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    s[0] = 0;
    for (int i = 0; i < n; i++)
        s[i + 1] = s[i] + q[i];

    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", s[r] - s[l - 1]);
    }

    return 0;
}