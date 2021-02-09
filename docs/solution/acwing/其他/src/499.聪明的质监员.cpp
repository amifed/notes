#include <iostream>
using namespace std;
using LL = long long;
const int N = 2e5 + 7;

int n, m;
LL S;
int w[N], v[N];
int L[N], R[N];
int c[N];
LL s[N];

LL get(int W) {
    for (int i = 1; i <= n; ++i) {
        if (w[i] >= W)
            s[i] = s[i - 1] + v[i], c[i] = c[i - 1] + 1;
        else
            s[i] = s[i - 1], c[i] = c[i - 1];
    }
    LL ans = 0;
    for (int i = 0; i < m; ++i)
        ans += (c[R[i]] - c[L[i] - 1]) * (s[R[i]] - s[L[i] - 1]);
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &S);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &w[i], &v[i]);
    for (int i = 0; i < m; ++i)
        scanf("%d%d", &L[i], &R[i]);
    int l = 0, r = 1e6;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (get(mid) >= S)
            l = mid;
        else
            r = mid - 1;
    }
    printf("%lld", min(abs(get(r) - S), abs(S - get(r + 1))));
    return 0;
}