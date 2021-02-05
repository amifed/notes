#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
int n, m;
int h[N], idx;

void down(int x) {
    int t = x;
    if (x * 2 <= idx && h[x * 2] < h[t]) t = x * 2;
    if (x * 2 + 1 <= idx && h[x * 2 + 1] < h[t]) t = x * 2 + 1;
    if (t != x) {
        swap(h[x], h[t]);
        down(t);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    idx = n;
    
    for (int i = n / 2; i; --i) down(i);
    
    while (m--) {
        printf("%d ", h[1]);
        h[1] = h[idx--];
        down(1);
    }
    return 0;
}