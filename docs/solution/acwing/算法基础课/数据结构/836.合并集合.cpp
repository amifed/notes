#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int p[N];
int n, m;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    scanf("%d%d", &n, &m);
    // 初始化
    for (int i = 1; i <= n; ++i)
        p[i] = i;

    while (m--) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (op[0] == 'M') p[find(a)] = find(b);
        else printf("%s\n", find(a) == find(b) ? "Yes" : "No");
    }
    return 0;
}