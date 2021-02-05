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
#define x first
#define y second
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
const int N = 1e2 + 7;

int m, n;
char g[N][N];
PII q[N * N];
int top;

double getDist(PII a, PII b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double getHash() {
    double s = 0;
    for (int i = 0; i < top; ++i) {
        for (int j = i + 1; j < top; ++j) {
            s += getDist(q[i], q[j]);
        }
    }
    return s;
}

char getId(double key) {
    static double hash[30];
    static int idx = 0;
    for (int i = 0; i < idx; ++i) {
        if (fabs(key - hash[i]) < EPS) return i + 'a';
    }
    hash[idx++] = key;
    return idx - 1 + 'a';
}

void dfs(int r, int c) {
    q[top++] = {r, c};
    g[r][c] = '0';
    for (int i = r - 1; i <= r + 1; ++i) {
        for (int j = c - 1; j <= c + 1; ++j) {
            if (i == r && j == c) continue;
            if (0 <= i && i < m && 0 <= j && j < n && g[i][j] == '1') 
                dfs(i, j);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> g[i];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '1') {
                top = 0, dfs(i, j);
                char c = getId(getHash());
                for (int k = 0; k < top; ++k) g[q[k].x][q[k].y] = c;
            }
        }
    }

    for (int i = 0; i < m; ++i) cout << g[i] << '\n';
    
    return 0;
}