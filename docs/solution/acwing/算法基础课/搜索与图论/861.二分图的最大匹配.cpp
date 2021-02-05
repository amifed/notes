#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 507, M = 1e5 + 7;

int n1, n2, m; // n1表示第一个集合中的点数，n2表示第二个集合中的点数
int h[N], e[M], ne[M],
    idx; // 邻接表存储所有边，匈牙利算法中只会用到从第一个集合指向第二个集合的边，所以这里只用存一个方向的边
int match[N]; // 存储第二个集合中的每个点当前匹配的第一个集合中的点是哪个
int vt[N];    // 表示第二个集合中的每个点是否已经被遍历过
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

bool find(int x) {
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!vt[j]) {
            vt[j] = 1;
            if (match[j] == 0 || find(match[j])) {
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n1, &n2, &m);
    while (m--) {
        int a, b;
        add(a, b);
    }

    int ans = 0;
    for (int i = 1; i <= n1; i++) {
        memset(vt, 0, sizeof vt);
        if (find(i)) ans++;
    }
}