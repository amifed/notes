#include <iostream>
using namespace std;
using LL = long long;

const int N = 1e5 + 7;
int n;
int a[N], b[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) b[i] = a[i] - a[i - 1];
    LL pos = 0, neg = 0;
    for (int i = 2; i <= n; ++i) {
        if (b[i] > 0) pos += b[i];
        else neg -= b[i];
    }
    cout << min(pos, neg) + abs(pos - neg) << endl;
    cout << abs(pos - neg) + 1;
    return 0;
}