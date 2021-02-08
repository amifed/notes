#include <iostream>
using namespace std;

const int N = 1e6 + 7;
using LL = long long;

int n, m;
int r[N], d[N], s[N], t[N];
LL b[N];

bool check(int mid) {
    for (int i = 1; i < n; ++i) b[i] = r[i] - r[i - 1];
    for (int i = 1; i <= mid; ++i) {
        b[s[i]] -= d[i], b[t[i] + 1] += d[i];
    }
    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1];
        if (b[i] < 0) return 1;
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &r[i]);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &d[i], &s[i], &t[i]);
    if (!check(m)) {
        puts("0");
        return 0;
    }
    int l = 1, r = m;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("-1\n%d", l);
    return 0;
}