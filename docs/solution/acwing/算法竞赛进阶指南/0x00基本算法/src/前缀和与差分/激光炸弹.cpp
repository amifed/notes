#include <iostream>
using namespace std;

const int N = 5e3 + 7;

int n, m;
int s[N][N];

int main() {
    int T, R;
    cin >> T >> R;
    R = min(5001, R);
    n = m = 5001;
    for (int i = 0, x, y, w; i < T; ++i) {
        cin >> x >> y >> w;
        ++x, ++y;
        s[x][y] += w;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (int i = R; i <= n; ++i) {
        for (int j = R; j <= m; ++j) {
            ans = max(ans, s[i][j] - s[i - R][j] - s[i][j - R] + s[i - R][j - R]);
        }
    }
    cout << ans;
    return 0;
}