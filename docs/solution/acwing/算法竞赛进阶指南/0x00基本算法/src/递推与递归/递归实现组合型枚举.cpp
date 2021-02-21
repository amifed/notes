#include <iostream>
using namespace std;

const int N = 17;

int n, m;
int tk[N];

void dfs(int k, int idx) {
    if (k >= n) {
        if (idx == m) {
            for (int i = 0; i < idx; ++i) printf("%d ", tk[i]);
            puts("");
        }
        return;
    }
    
    tk[idx] = k + 1;
    dfs(k + 1, idx + 1);
    
    dfs(k + 1, idx);
}

int main() {
    cin >> n >> m;
    dfs(0, 0);
    return 0;
}