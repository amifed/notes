#include <iostream>
using namespace std;

const int N = 17;

int n;
int tk[N];

void dfs(int k, int state) {
    if (k >= n) {
        for (int i = 0; i < n; ++i) printf("%d ", tk[i]);
        puts("");
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!(state >> i & 1)) {
            tk[k] = i + 1;
            dfs(k + 1, state + (1 << i));
        }
    }
}

int main() {
    cin >> n;
    dfs(0, 0);
    return 0;
}