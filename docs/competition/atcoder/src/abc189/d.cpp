// Problem: D - Logical Expression
// Contest: AtCoder - AtCoder Beginner Contest 189
// URL: https://atcoder.jp/contests/abc189/tasks/abc189_d
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
const int N = 67;

int n;
string op[N];
LL dp[N][2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> op[i];
	dp[0][0] = 1, dp[0][1] = 1;
	for (int i = 1; i <= n; ++i) {
		if (op[i - 1] == "AND") {
			dp[i][0] += dp[i - 1][0] * 2 + dp[i - 1][1];
			dp[i][1] += dp[i - 1][1];
		} else {
			dp[i][0] += dp[i - 1][0];
			dp[i][1] += dp[i - 1][0] + dp[i - 1][1] * 2;
		}
	}
	cout << dp[n][1];
    return 0;
}