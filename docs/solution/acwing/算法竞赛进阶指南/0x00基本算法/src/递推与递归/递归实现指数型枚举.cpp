#include <iostream>
using namespace std;

const int N = 17;

int n;
int tk[N];

void dfs(int k, int idx) {
    if (k >= n) {
        for (int i = 0; i < idx; ++i) printf("%d ", tk[i]);
        puts("");
        return;
    }
    
    dfs(k + 1, idx);
    
    tk[idx] = k + 1;
    dfs(k + 1, idx + 1);
}

int main() {
    cin >> n;
    dfs(0, 0);
    return 0;
}