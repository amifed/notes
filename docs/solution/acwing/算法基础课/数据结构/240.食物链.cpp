#include <iostream>
using namespace std;

const int N = 5e5 + 7;
int n, m, p[N], d[N];

int find(int x) {
    if (p[x] != x) {
        int t = find(p[x]);
        d[x] += d[p[x]];
        p[x] = t;
    }
    return p[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) p[i] = i;
    int ans = 0;
    while (m--) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (x > n || y > n) {
            ++ans;
            continue;
        }
        int px = find(x), py = find(y);
        if (t == 1) {
            if (px == py && (d[x] - d[y]) % 3) ++ans; // 如果两个结点在根结点相同，说明已经合并过，判断距离是否 %3 相同（同类）
            else if (px != py) p[px] = py, d[px] = d[y] - d[x]; //(d[x] + d[px]) % 3 == d[y] % 3
        } else {
            if (px == py && (d[x] - d[y] - 1) % 3) ++ans; // 如果两个结点在根结点相同，说明已经合并过，判断距离是否 %3 == 1（吃与被吃距离差1）
            else if (px != py) p[px] = py, d[px] = d[y] - d[x] + 1;  //(d[x] + d[px]) % 3 == (d[y] + 1) % 3
        }
    }
    printf("%d", ans);
    return 0;
}
