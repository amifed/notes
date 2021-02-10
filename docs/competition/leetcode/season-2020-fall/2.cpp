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

int bsearch(vector<int> &q, int x) {
    int l = 0, r = q.size() - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (q[mid] <= x)
            l = mid;
        else
            r = mid - 1;
    }
    if (q[l] <= x) return l;
    return 0;
}
int main() {
    vector<int> q = {2, 5, 5};
    cout << bsearch(q, 1);
    return 0;
}