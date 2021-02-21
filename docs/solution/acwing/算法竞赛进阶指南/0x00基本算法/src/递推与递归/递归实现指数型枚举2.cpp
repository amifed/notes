#include <iostream>
using namespace std;

const int N = 17;

int n;

void dfs(int k, int state) {
    if (k >= n) {
        for (int i = 0; i < n; ++i) {
            if (state & 1 << i) printf("%d ", i + 1);
        }
        puts("");
        return;
    }
    
    dfs(k + 1, state);
    dfs(k + 1, state + (1 << k));
}

int main() {
    cin >> n;
    dfs(0, 0);
    return 0;
}