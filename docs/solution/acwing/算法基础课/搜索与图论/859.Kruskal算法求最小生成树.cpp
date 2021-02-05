#include <algorithm>
#include <iostream>
using namespace std;

const int N = 2e5 + 7, INF = 0x3f3f3f3f;
int n, m, p[N];
struct Edge {
    int u, v, w;
    bool operator<(const Edge &e)const { return w < e.w; }
} edges[N];

int find(int x) {
    if (x != p[x]) return p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        u = find(u), v = find(v);
        if (u != v) {
            p[u] = v;
            ans += w;
            cnt++;
        }
    }
    if (cnt < n - 1) return INF;
    else return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[i] = {u, v, w};
    }
    int ans = kruskal();
    if (ans == INF) printf("impossible");
    else printf("%d", ans);
}