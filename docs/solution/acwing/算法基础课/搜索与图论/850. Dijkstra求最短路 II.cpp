#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 1e6 + 7;
const int M = 1e6 + 7;
int h[N], w[M], e[M], ne[M], idx;
int n, m, d[N], vt[N];
void add(int u, int v, int x) {
    e[idx] = v, w[idx] = x, ne[idx] = h[u], h[u] = idx++;
}
void dijkstra(int s) {
    memset(vt, 0, sizeof vt);
    memset(d, 0x3f, sizeof d);
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<PII>> pq; //最小堆
    d[s] = 0;
    pq.push({0, s}); //将 起点入队，{距离，结点编号}
    while (!pq.empty()) {
        auto t = pq.top(); //起点出发到达的距离最短结点
        pq.pop();
        int u = t.second, dist = t.first;
        if (vt[u]) continue; //之前更新过，冗余
        vt[u] = 1;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (d[v] > w[i] + dist) { // u为中介点，优化结点 u 能到达的结点 v
                                      // 之间的最短距离
                d[v] = w[i] + dist;
                pq.push({d[v], v});
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    idx = 0;
    memset(h, -1, sizeof h);
    int u, v, x;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &x);
        add(u, v, x);
    }
    dijkstra(1);
    printf("%d\n", d[n] == INF ? -1 : d[n]);
    return 0;
}