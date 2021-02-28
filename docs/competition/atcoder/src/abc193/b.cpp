// Problem: B - Play Snuke
// Contest: AtCoder - Caddi Programming Contest 2021(AtCoder Beginner Contest
// 193) URL: https://atcoder.jp/contests/abc193/tasks/abc193_b Memory Limit:
// 1024 MB Time Limit: 2000 ms

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

struct APX {
    int a, p, x;
} apx[N];
int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> apx[i].a >> apx[i].p >> apx[i].x;
    sort(apx, apx + n, [](const APX &u, const APX &v) { return u.a < v.a; });
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        if (apx[i].x - apx[i].a > 0) ans = min(ans, apx[i].p);
    }
    if (ans == INF)
        cout << -1;
    else
        cout << ans;

    return 0;
}