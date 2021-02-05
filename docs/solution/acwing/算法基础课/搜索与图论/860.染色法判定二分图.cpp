#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1007, M = 2e5 + 7;
int n, m;
int h[N], e[M], ne[M], idx;
int color[N];
int add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int u, int c) {
    color[u] = c;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (color[j] = -1) {
            if (!dfs(j, !c)) return false;
        } else if (color[j] == c)
            return false;
    }
    return true;
}
bool check() {
    memset(color, -1, sizeof color);
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (color[i] == -1)
            if (!dfs(i, 0)) {
                flag = false;
                break;
            }
    return flag;
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }    
    if (check()) printf("Yes");
    else printf("No");
}
