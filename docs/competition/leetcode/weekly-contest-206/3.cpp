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

const int N = 1007;
int n, m, p[N];
struct Edge {
    int u, v, w;
    bool operator<(const Edge &e) const { return w < e.w; }
} edges[N * N];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

class Solution {
public:
    int kruskal() {
        int ans = 0, cnt = 0;
        for (int i = 0; i < n; i++)
            p[i] = i;
        sort(edges, edges + m);
        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            u = find(u), v = find(v);
            if (u != v) ans += w, cnt++, p[u] = v;
            if (cnt == n - 1) break;
        }
        return ans;
    }
    int minCostConnectPoints(vector<vector<int>> &ps) {
        n = ps.size();
        m = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int w = abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]);
                edges[m++] = {i, j, w};
            }
        return kruskal();
    }
};