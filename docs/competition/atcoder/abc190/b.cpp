// Problem: B - Magic 3
// Contest: AtCoder - AtCoder Beginner Contest 190
// URL: https://atcoder.jp/contests/abc190/tasks/abc190_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;
const int N = 1e2 + 7;

int n, s, d;
int x[N], y[N];

int main() {
    cin >> n >> s >> d;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    bool ans = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i] < s && y[i] > d) ans = 1;
    }
    if (ans)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}