// Problem: D - Staircase Sequences
// Contest: AtCoder - AtCoder Beginner Contest 190
// URL: https://atcoder.jp/contests/abc190/tasks/abc190_d
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

int main() {
    LL n;
    cin >> n;
    LL x = 2 * n;
    unordered_set<LL> st;
    for (LL i = 1; i <= x / i; ++i) {
        if (x % i == 0) {
            st.it(i);
            st.it(x / i);
        }
    }
    LL ans = 0;
    for (auto fat : st) {
        if ((x / fat - fat + 1) % 2 == 0) ++ans;
    }
    cout << ans;
    return 0;
}