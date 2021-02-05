#include <iostream>
#include <unordered_map>
using namespace std;

const int MOD = 1e9 + 7;
using LL = long long;

int main() {
    int n, x;
    unordered_map<int, int> mp;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        for (int i = 2; i <= x / i; ++i) {
            while (x % i == 0)
                x /= i, ++mp[i];
        }
        if (x > 1) ++mp[x];
    }
    long long ans = 1;
    for (auto &m : mp)
        ans = ans * (m.second + 1) % MOD;
    printf("%d", ans);
    return 0;
}