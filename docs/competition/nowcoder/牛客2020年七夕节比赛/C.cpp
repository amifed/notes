#include <bits/stdc++.h>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define all(v) (v).begin(), (v).end()
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e5 + 7;

class Solution {
public:
};

int main() {
    Solution sn;
    int n;
    cin >> n;
    cout << "I love U forever.\n";
    int m = 5 + 6 * (n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < i * 2 + n; j++) {
            printf("*");
        }
        for (int j = 0; j < m - (i * 2 + n) * 2 - (n - i) * 2; j++) {
            printf(" ");
        }
        for (int j = 0; j < i * 2 + n; j++) {
            printf("*");
        }
        puts("");
    }
    for (int i = m; i >= 1; i -= 2) {
        for (int j = 0; j < (m - i) / 2; j++) {
            printf(" ");
        }
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        puts("");
    }
    return 0;
}