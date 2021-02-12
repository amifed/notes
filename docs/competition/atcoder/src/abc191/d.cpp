// Problem: D - Circle Lattice Points
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
using LL = long long;
using LD = long double;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 1e5 + 7;

double X, Y, R;

LD getDist(LD a, LD b) {
    LD dx = a - X, dy = b - Y;
    return sqrt(dx * dx + dy * dy);
}

int get(int x) {
    int l = floor(Y - R), r = ceil(Y + R);
    if (getDist(x, r + l / 2) > R) return 0;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        // cout << x << ',' << mid << ' ';
        if (getDist(x, mid) <= R)
            l = mid;
        else
            r = mid - 1;
    }
    int t = l;
    l = floor(Y - R), r = ceil(Y + R);
    while (l < r) {
        int mid = (l + r) >> 1;
        // cout << x << ',' << mid << ' ';
        if (getDist(x, mid) <= R)
            r = mid;
        else
            l = mid + 1;
    }
    // if (x == 0) cout << t << '=' << l;
    if (t <= l) return getDist(x, t) <= R;
    return t - l + 1;
}

int main() {
    cin >> X >> Y >> R;
    int xl = floor((X - R)), xr = ceil(X + R);
    int ans = 0;
    for (int i = xl; i <= xr; ++i) {
        ans += get(i);
        // cout << endl;
    }
    cout << ans;
    return 0;
}