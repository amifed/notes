#include <iostream>
using namespace std;

const int N = 1e3 + 7;
const int MOD = 1e9 + 7;
int n;
int C[N][N];

int main() {
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <=i; ++j) {
            if (!j) C[i][j] = 1;
            else C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
        }
    }
    int ans = 0;
    for (int k = 2; k <= n - 2; ++k) {
        ans = ans + 1LL * C[n-1][k] * (k-1) % MOD * (n-k-1);
    }
    cout << ans;
    return 0;
}
