// Problem: A - B = C
// Contest: AtCoder - AtCoder Regular Contest 112
// URL: https://atcoder.jp/contests/arc112/tasks/arc112_a
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
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 1e5 + 7;

int T;
int L, R;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> L >> R;
        int k = R - 2 * L;
        if (k < 0) {
            cout << 0 << '\n';
            continue;
        }
        LL ans = 0;
        if (k & 1) {
            ans += 1LL * (1 + k) * (1 + k) / 2;
        } else {
            ans += 1LL * (2 + k) * k / 2;
        }
        ans += R / 2 - L + 1;
        cout << ans << '\n';
    }
    return 0;
}