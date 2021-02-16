// Problem: A - Vanishing Pitch
// Contest: AtCoder - AtCoder Beginner Contest 191
// URL: https://atcoder.jp/contests/abc191/tasks/abc191_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;

int v, t, s, d;
int main() {
    cin >> v >> t >> s >> d;
    if (d < v * t || d > v * s)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}