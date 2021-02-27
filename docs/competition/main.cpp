#include <iostream>
using namespace std;

const int N = 3e5 + 7, M = 9e6 + 7;

int n, m;
int a[N], b[N];
int son[M][2], idx;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int &s = son[p][x >> i & 1];
        if (!s) s = ++idx;
        p = s;
    }
}

int dfs(int x, int i, int p, int cnt) {
    printf("%d %d %d %d\n", x, i, p, cnt);
    if (cnt >= 2) {
        if (!son[p][0] && !son[p][1]) return 1;
        return 0;
    }
    int ans = 0;
    if (son[p][0]) ans += dfs(x, i - 1, son[p][0], cnt + (x >> i & 1));
    if (son[p][1]) ans += dfs(x, i - 1, son[p][1], cnt + !(x >> i & 1));
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        insert(a[i]);
    }
    int ans = 0;
    for (int i = 0; i <= idx; ++i) {
        cout << i << ' ';
        for (int j = 0; j < 2; ++j) {
            cout << son[i][j] << ' ';
        }
        cout << endl;
    }
    cout << dfs(2, 30, 0, 0);
    // for (int i = 0; i < m; ++i) {
    //     int x;
    //     cin >> x;
    //     ans += dfs(x, 30, 0, 0);
    // }
    // cout << ans;
    return 0;
}
