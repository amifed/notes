#include <iostream>

const int N = 1e5 + 7;

int p[N], size[N];
int n, m;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) p[i] = i, size[i] = 1;
    while (m--) {
        int a, b;
        char op[3];
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d%d", &a, &b);
            int x = find(a), y = find(b);
            if (x != y) size[y] += size[x], p[x] = y; 
        } else if (op[1] == '1') {
            scanf("%d%d", &a, &b);
            printf("%s\n", find(a) == find(b) ? "Yes" : "No");
        } else {
            scanf("%d", &a);
            printf("%d\n", size[find(a)]);
        }
    }
    return 0;
}