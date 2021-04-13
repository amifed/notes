// Problem: A. Review Site
// Contest: Codeforces - Educational Codeforces Round 107 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1511/problem/0
// Memory Limit: 256 MB
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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int u1, d1, u2, d2, ans;
        u1 = d1 = u2 = d2 = ans = 0;
        while (n--) {
            int x;
            cin >> x;
            if (x == 1) {
                u1++, ans++;
            } else if (x == 2) {
                d2++;
            } else {
                if (u1 >= d1)
                    u1++, ans++;
                else if (u2 >= d2)
                    u2++, ans++;
                else
                    d1++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}