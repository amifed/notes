// Problem: E - Rotate and Flip
// Contest: AtCoder - AtCoder Beginner Contest 189
// URL: https://atcoder.jp/contests/abc189/tasks/abc189_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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
const int N = 2e5 + 7;

int n, o, q;
int x[N][N], y[N][N];

void rotate(int idx) {
    for (int i = 0; i < n; ++i) {
        int tx = x[i][idx], ty = y[i][idx];
        x[i][idx + 1] = abs(ty);
        y[i][idx + 1] = abs(tx);
        if ((tx ^ ty) >= 0) {
            y[i][idx + 1] = -y[i][idx + 1];
        } else {
            x[i][idx + 1] = -x[i][idx + 1];
        }
    }
}

void rotateR(int idx) {
    for (int i = 0; i < n; ++i) {
        int tx = x[i][idx], ty = y[i][idx];
        x[i][idx + 1] = abs(ty);
        y[i][idx + 1] = abs(tx);
        if ((tx ^ ty) >= 0) {
            x[i][idx + 1] = -x[i][idx + 1];
        } else {
            y[i][idx + 1] = -y[i][idx + 1];
        }
    }
}

void flipX(int idx, int d) {
    for (int i = 0; i < n; ++i) {
        x[i][idx + 1] = x[i][idx] + d - x[i][idx];
    }
}

void flipY(int idx, int d) {
    for (int i = 0; i < n; ++i) {
        y[i][idx + 1] = y[i][idx] + d - y[i][idx];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d %d", &x[i][0], &y[i][0]);
    scanf("%d", &o);
    for (int i = 0; i < 0; ++i) {
        int d, p;
        if (d == 1)
            rotate(i);
        else if (d == 2)
            rotateR(i);
        else if (d == 3) {
            scanf("%d", &p);
            flipX(i, p);
        } else if (d == 4) {
            scanf("%d", &p);
            flipY(i, p);
        }
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d %d\n", x[b][a], y[b][a]);
    }
    return 0;
}