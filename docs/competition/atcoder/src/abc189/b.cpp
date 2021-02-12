// Problem: B - Alcoholic
// Contest: AtCoder - AtCoder Beginner Contest 189
// URL: https://atcoder.jp/contests/abc189/tasks/abc189_b
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
const int N = 1e3 + 7;

int n, x;
int d[N], p[N];

int main() {
	scanf("%d %d", &n, &x);
	for (int i = 0; i < n; ++i) scanf("%d %d", &d[i], &p[i]);
	int i = 0;
	int cnt = 0;
	while (i < n) {
		cnt += d[i] * p[i];
        // cout << cnt << ' ';
		if (cnt > x * 100) break;
		++i;
	}
	if (i < n) printf("%d", i + 1);
	else printf("-1");
    return 0;
}