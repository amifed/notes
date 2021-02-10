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
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 7;

const int N = 107;
int x[N], y[N];

int main() {
    int n;
    scanf("%d", &n);
    bool ans = false;
    for (int i = 0; i < n; ++i)
        scanf("%d %d", &x[i], &y[i]);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (x[i] == x[j] && x[i] == x[k] ||
                    y[i] == y[j] && y[i] == y[k]) {
                    puts("Yes");
                    return 0;
                } else if (double(y[i] - y[j]) / double(x[i] - x[j]) ==
                           double(y[i] - y[k]) / double(x[i] - x[k])) {
                    puts("Yes");
                    return 0;
                }
            }
        }
    }
    puts("No");
    return 0;
}