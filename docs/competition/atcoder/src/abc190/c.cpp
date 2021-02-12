// Problem: C - Bowls and Dishes
// Contest: AtCoder - AtCoder Beginner Contest 190
// URL: https://atcoder.jp/contests/abc190/tasks/abc190_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;

const int N = 107;

int n, m, k;
int a[N][2], d[N][2];
int p[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> a[i][0] >> a[i][1];
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> d[i][0] >> d[i][1];

    int ans = 0;
    for (int x = 0; x < 1 << k; ++x) {
        int t = 0;
        memset(p, 0, sizeof p);
        for (int i = 0; i < k; ++i) {
            ++p[d[i][x & 1 << i ? 0 : 1]];
        }
        for (int i = 0; i < m; ++i) {
            t += (p[a[i][0]] && p[a[i][1]]);
        }
        ans = max(ans, t);
    }
    cout << ans << endl;
    return 0;
}