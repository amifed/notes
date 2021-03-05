#include <iostream>
#define x first
#define y second
using namespace std;

const int N = 1e5 + 7;

int n, m;
pair<string, int> ops[N];

int cacl(int bit, int now) {
    for (int i = 1; i <= n; ++i) {
        int x = ops[i].y >> bit & 1;
        if (ops[i].x == "AND") now &= x;
        else if (ops[i].x == "OR") now |= x;
        else now ^= x;
    }
    return now;
}

int main () {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> ops[i].x >> ops[i].y;
    int val = 0, ans = 0;
    for (int bit = 29; bit >= 0; --bit) {
        int ret0 = cacl(bit, 0);
        int ret1 = cacl(bit, 1);
        if (val + (1 << bit) <= m && ret0 < ret1) 
            val += 1 << bit, ans ^= ret1 << bit;
        else ans ^= ret0 << bit;
    }
    cout << ans;
    return 0;
}