#include <iostream>
using namespace std;

const int N = 1e5 + 7;
const double EPS = 1e-5;

int n, m;
int a[N];
double s[N];

bool check(double mid) {
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i] - mid;
    double mi = 0;
    for (int i = 0, j = m; j <= n; ++i, ++j) {
        mi = min(mi, s[i]);
        if (s[j] - mi >= 0) return 1;
    }
    return 0;
}

int main() {
    cin >> n >> m;
    double l = 0, r = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        r = max(r, (double)a[i]);
    }
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << int(r * 1000);
    return 0;
}