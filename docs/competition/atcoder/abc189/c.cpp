// Problem: C - Mandarin Orange
// Contest: AtCoder - AtCoder Beginner Contest 189
// URL: https://atcoder.jp/contests/abc189/tasks/abc189_c
// Memory Limit: 1024 MB
// Time Limit: 1500 ms
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
const int N = 1e5 + 7;

int n;
int p[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &p[i]);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
    	int minn = p[i];
    	for (int j = i; j < n; ++j) {
    		minn = min(minn, p[j]);
    		ans = max(ans, minn * (j - i + 1));
    	}
    }
    printf("%d", ans);
    return 0;
}