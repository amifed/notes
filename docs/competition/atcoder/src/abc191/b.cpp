// Problem: B - Remove It
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_b
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

int n, x;

int main() {
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if (a != x) cout << a << ' ';
    }
    cout << endl;
    return 0;
}