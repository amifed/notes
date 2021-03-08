#include <iostream>
using namespace std;

const int MOD = 9901;

int A, B;

int fastPow(int a, int b) {
    a %= MOD;
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

int sum(int p, int k) {
    if (k == 0) return 1;
    if (k & 1) return (1 + 1LL * fastPow(p, k / 2 + 1)) * sum(p, k / 2) % MOD;
    return (1LL * sum(p, k - 1) * p + 1) % MOD;
}

int main() {
    cin >> A >> B;
    int ans = 1;
    for (int i = 2; i <= A; ++i) {
        int s = 0;
        while (A % i == 0) A /= i, ++s;
        ans = ans * sum(i, s * B) % MOD;
    }
    if (!A) ans = 0;
    cout << ans << endl;
    return 0;
}