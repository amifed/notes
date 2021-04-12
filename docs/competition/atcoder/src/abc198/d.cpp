// Problem: D - Send More Money
// Contest: AtCoder - AtCoder Beginner Contest 198
// URL: https://atcoder.jp/contests/abc198/tasks/abc198_d
// Memory Limit: 1024 MB
// Time Limit: 5000 ms

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

string a, b, c;

bool work(int x, int y, int z) {
    string sx = to_string(x);
    string sy = to_string(y);
    string sz = to_string(z);
    if (sz.size() != c.size()) return 0;
    unordered_map<char, char> c2n, n2c;
    for (int i = 0; i < sx.size(); ++i) {
        if (c2n.count(a[i])) {
            if (c2n[a[i]] != sx[i]) return 0;
        } else if (n2c.count(sx[i])) {
            if (n2c[sx[i]] != a[i]) return 0;
        } else {
            c2n[a[i]] = sx[i];
            n2c[sx[i]] = a[i];
        }
    }
    for (int i = 0; i < sy.size(); ++i) {
        if (c2n.count(b[i])) {
            if (c2n[b[i]] != sy[i]) return 0;
        } else if (n2c.count(sy[i])) {
            if (n2c[sy[i]] != b[i]) return 0;
        } else {
            c2n[b[i]] = sy[i];
            n2c[sy[i]] = b[i];
        }
    }
    for (int i = 0; i < sz.size(); ++i) {
        if (c2n.count(c[i])) {
            if (c2n[c[i]] != sz[i]) return 0;
        } else if (n2c.count(sz[i])) {
            if (n2c[sz[i]] != c[i]) return 0;
        } else {
            c2n[c[i]] = sz[i];
            n2c[sz[i]] = c[i];
        }
    }
    return 1;
}

void run() {
    int na = a.size(), nb = b.size();
    for (int i = (int)pow(10, na - 1); i < (int)pow(10, na); ++i) {
        for (int j = (int)pow(10, nb - 1); j < (int)pow(10, nb); ++j) {
            // cout << i << ' ' << j << ' ' << i + j << endl;
            if (work(i, j, i + j)) {
                cout << i << endl;
                cout << j << endl;
                cout << i + j << endl;
                return;
            }
        }
    }
    cout << "UNSOLVABLE";
}

int main() {
    cin >> a >> b >> c;
    run();

    return 0;
}