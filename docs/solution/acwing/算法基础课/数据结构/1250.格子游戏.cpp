#include <iostream>
using namespace std;

const int N = 4e5 + 7;
int p[N];
int n, m;

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n * n; ++i) p[i] = i;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        char op[2];
        scanf("%d%d%s", &a, &b, op);
        int x, y;
        if (op[0] == 'D') x = a + 1, y = b;
        else x = a, y = b + 1;
        int rx = find (a * (n - 1) + b), ry = find(x * (n - 1) + y);
        if (rx == ry) {
            printf("%d", i);
            return 0;
        }
        p[rx] = ry;
    }
    printf("draw");
    return 0;
}