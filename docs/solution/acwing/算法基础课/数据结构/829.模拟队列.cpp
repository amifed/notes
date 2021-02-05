#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int m, q[N], hh, tt;

int main() {
    hh = tt = 0;
    cin >> m;
    while (m --) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            q[tt++] = x;
        } else if (op == "pop") hh++;
        else if (op == "empty")
            cout << (hh == tt ? "YES" : "NO") << endl;
        else cout << q[hh] << endl;
    }
    return 0;
}