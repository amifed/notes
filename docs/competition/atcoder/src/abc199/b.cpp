// Problem: B - Intersection
// Contest: AtCoder - AtCoder Beginner Contest 199（Sponsored by Panasonic）
// URL: https://atcoder.jp/contests/abc199/tasks/abc199_b
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
const int N = 1e5 + 7;

int n;
int a[N], b[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int x = 1; x <= 1000; ++x) {
    	bool flag = 1;
    	for (int i = 0; i < n; ++i) {
    		if (a[i] > x || x > b[i]) {
    			flag = 0;
    			break;
    		}
    	}
    	if (flag) {
    		cout << x;
    		return 0;
    	}
    }
    cout << 0;
    
    return 0;
}