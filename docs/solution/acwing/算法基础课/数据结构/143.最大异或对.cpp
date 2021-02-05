#include <iostream>
using namespace std;

const int N = 1e5 + 7, M = 31 * N;
int son[M][2], idx;
int n, a[N];

void insert(int x) {
    int p = 0;
    for (int i = 31; i >= 0; --i) {
        int q = (x >> i) & 1;
        if (!son[p][q]) son[p][q] = ++idx;
        p = son[p][q];
    }
}
int search(int x) {
    int ans = 0, p = 0;
    for (int i = 31; i >= 0; --i) {
        int q = (x >> i) & 1;
        if (son[p][!q]) p = son[p][!q], ans += (1 << i);
        else p = son[p][q];
    }
    return ans;
}

int main() {
    idx = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        insert(a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, search(a[i]));
    } 
    printf("%d", ans);
    return 0;
}