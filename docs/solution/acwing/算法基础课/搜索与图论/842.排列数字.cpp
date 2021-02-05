#include <iostream>
using namespace std;

const int N = 10;
int n, path[N], vt[N];

void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; ++i) printf("%d ", path[i]);
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!vt[i]) {
            vt[i] = 1;
            path[u] = i;
            dfs(u + 1);
            vt[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(0);
    return 0;
}