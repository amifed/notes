#include <iostream>
using namespace std;

int fastPow(int a, int b, int p) {
    if (b == 0) return 1 % p;
    int tmp = fastPow(a, b >> 1, p) % p;
    if (b & 1) return 1LL * tmp * tmp % p * a % p;
    return 1LL * tmp * tmp % p;
}

int fastPow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1LL * ans * a % p;
        a = 1LL * a * a % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    printf("%d", fastPow(a, b, p));
    return 0;
}