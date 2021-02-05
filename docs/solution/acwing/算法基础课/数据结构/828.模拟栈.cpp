#include <iostream>
using namespace std;

const int N = 1e5 + 7;

int m, stk[N], tt;

int main() {
    tt = -1;
    cin >> m;
    while (m--) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            stk[++tt] = x;
        } else if (op == "pop")
            tt--;
        else if (op == "empty")
            cout << (tt == -1 ? "YES" : "NO") << endl;
        else
            cout << stk[tt] << endl;
    }
    return 0;
}