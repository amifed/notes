#include <iostream>
using namespace std;

using LL = long long;
int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        LL a = k - 1 + 1LL * k * y;
        printf("%lld\n", (a + x - 2) / (x - 1) + k);
    }
    return 0;
}