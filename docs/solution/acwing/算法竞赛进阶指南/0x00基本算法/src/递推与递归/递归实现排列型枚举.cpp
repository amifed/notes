#include <iostream>
using namespace std;

const int N = 17;

int n;
bool vt[N];
int tk[N];

void dfs(int k) {
    if (k >= n) {
        for (int i = 0; i < n; ++i) printf("%d ", tk[i]);
        puts("");
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!vt[i]) {
            vt[i] = 1, tk[k] = i + 1;
            dfs(k + 1);
            vt[i] = 0;
        }
    }
}

int main() {
    cin >> n;
    dfs(0);
    return 0;
}