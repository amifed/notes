#include <iostream>
using namespace std;
const int N = 17;

int n, p[N];

void dfs(int k) {
    if (k == n) {
        for (int i = 0; i < n; ++i)
            cout << p[i] << ' ';
        cout << '\n';
        return;
    }
    for (int i = k; i < n; ++i) {
        swap(p[k], p[i]);
        dfs(k + 1);
        swap(p[k], p[i]);
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    dfs(0);
    return 0;
}