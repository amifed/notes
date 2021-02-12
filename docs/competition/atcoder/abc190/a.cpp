// Problem: A - Very Very Primitive Game
// Contest: AtCoder - AtCoder Beginner Contest 190
// URL: https://atcoder.jp/contests/abc190/tasks/abc190_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    if (a + c > b)
        cout << "Takahashi";
    else
        cout << "Aoki";
    return 0;
}