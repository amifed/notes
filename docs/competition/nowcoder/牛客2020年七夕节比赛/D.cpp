#include <bits/stdc++.h>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e6 + 5;

class Solution {
public:
};
int ans;
void f(int n, int x, int s) {
    if (x == 1)
        x = 2;
    else
        ans = min(ans, s + n);
    for (; x * x < n; x++) {
        if (n % x == 0) {
            f(n / x, x + 1, s + x);
        }
    }
}
int dp[MAXN];
int main() {
    Solution sn;
    int n;
    ans = n + 1;
    f(n, 1, 0);
    cout << ans << endl;
    return 0;
}