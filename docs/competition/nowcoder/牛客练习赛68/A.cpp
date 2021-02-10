#include <bits/stdc++.h>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
#define forr(n, s, e) for (int(n) = (s); (n) < (e); (n)++)
#define rfor(n, s, e) for (int(n) = (s); (n) > (e); (n)--)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e5 + 7;

int v[MAXN];
int pre[MAXN], suf[MAXN];
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    forr(i, 1, n + 1) scanf("%d", &v[i]);
    pre[0] = suf[n + 1] = n;
    forr(i, 1, n + 1) pre[i] = min(pre[i - 1], v[i]);
    rfor(i, n, 0) suf[i] = min(suf[i + 1], v[i]);
    forr(i, 0, q) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", min(pre[l - 1], suf[r + 1]));
    }
    return 0;
}