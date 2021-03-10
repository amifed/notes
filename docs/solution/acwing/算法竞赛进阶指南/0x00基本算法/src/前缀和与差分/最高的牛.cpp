#include <iostream>
using namespace std;

const int N = 1e4 + 7;
int n, p, h, m;
bool vt[N][N];
int b[N];

int main() {
    cin >> n >> p >> h >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        if (vt[x][y]) continue;
        vt[x][y] = 1;
        b[x + 1] -= 1, b[y] += 1;
    }
    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1];
        cout << h + b[i] << endl;
    }
    return 0;
}