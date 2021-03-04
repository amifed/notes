#include <iostream>
using namespace std;
using LL = long long;

LL mul(LL a, LL b, LL p) {
    LL ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % p;
        a = 2 * a % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    LL a, b, p;
    cin >> a >> b >> p;
    cout << mul(a, b, p);
    return 0;
}