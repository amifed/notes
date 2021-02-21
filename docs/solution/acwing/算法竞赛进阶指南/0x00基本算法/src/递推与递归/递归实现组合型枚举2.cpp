#include <iostream>
using namespace std;

const int N = 17;

int n, m;

void dfs(int k, int s, int state) {
    if (s == m) {
        for (int i = 0; i < n; ++i) {
            if (state >> i & 1) printf("%d ", i + 1);
        }
        puts("");
        return;
    }
    if (k == n) return;
    for (int i = k; i < n; ++i) dfs(i + 1, s + 1, state + (1 << i));
}

int main() {
    cin >> n >> m;
    dfs(0, 0, 0);
    return 0;
}