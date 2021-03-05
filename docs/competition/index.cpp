#include <iostream>
using namespace std;
using LL = long long;
const int N = 1e4 + 7;
const int MOD = 998244353;
int n, m;
int a[N];
LL x[N];

int main() {    
    cin >> n;
    for (int i = 0; i <= n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> x[i];
    for (int i = 0; i < m; ++i) {
        LL ans = 1;
        for (int j = 1; j <= n; ++j) {
            ans = ans + 1LL * x[i] * a[j] % MOD;
            x[i] = x[i] * x[i] % MOD;
        }
        cout << ans << ' ';
    }
    return 0;
}

