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
const int MAXN = 1e5 + 5;
class Solution {
public:
};

int a[MAXN], f[MAXN];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a, a + n + 1);
    if (a[n] > n) {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] <= i) {
            f[i] = max(f[i - 1], f[i - a[i]] + 1);
        } else {
            f[i] = 0;
        }
    }
    cout << f[n] << endl;
    return 0;
}