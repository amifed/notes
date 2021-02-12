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

int n;
PII a[N];
int main() {
    scanf("%d", &n);
    LL sa = 0;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        a[i] = {x, y};
        sa += x;
    }
    sort(a, a + n, [](const PII &p, const PII &q) {
        return 1LL * 2 * p.first + p.second > 1LL * 2 * q.first + q.second;
    });
    LL sb = 0;
    for (int i = 0; i < n; ++i) {
        sa -= a[i].first, sb += a[i].first + a[i].second;
        if (sb > sa) {
            printf("%d", i + 1);
            break;
        }
    }
    return 0;
}   