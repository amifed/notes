// Problem: B - Remove It
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;

int n, x;

int main() {
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if (a != x) cout << a << ' ';
    }
    cout << endl;
    return 0;
}