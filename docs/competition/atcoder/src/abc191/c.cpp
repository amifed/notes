// Problem: C - Digital Graffiti
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;
const int N = 17;

int m, n;
char s[N][N];
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int main() {
    cin >> m >> n;
    for (int i = 0; i < m; ++i) cin >> s[i];
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s[i][j] == '.') continue;
            int t = 1;
            t += s[i+1][j] == '#';
            t += s[i][j+1] == '#';
            t += s[i+1][j+1] == '#';
            ans += t == 1 || t == 3;
        }
    }
    cout << ans;
    return 0;
}