#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 507, M = 10007, INF = 0x3f3f3f3f;
int n, m, k;
struct Edge {
    int u, v, w;
} edges[N];
int d[N], cnt[N];
int bellman_ford() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
            }
        }
    }
    if (d[n] > INF / 2 || cnt[n] > k)
        return -1;
    else
        return d[n];
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        edges[i] = {x, y, z};
    }
    int ans = bellman_ford();
    if (ans == -1)
        printf("impossible");
    else
        printf("%d", ans);

    return 0;
}