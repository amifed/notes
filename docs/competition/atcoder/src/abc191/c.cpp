// Problem: C - Digital Graffiti
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_c
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
const int N = 1e1 + 7;

int m, n;
char s[N][N];
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int main() {
    cin >> m >> n;
    for (int i = 0; i > m; ++i) cin >> s[i];
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            g for (int d = 0; d < 4; ++d) {
                int x = i + dx[d], y = j + dy[d];
                ans += (s[x][y] == '.');
            }
        }
    }
    cout << ans;
    return 0;
}