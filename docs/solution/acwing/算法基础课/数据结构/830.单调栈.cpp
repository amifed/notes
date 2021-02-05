#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int n, stk[N], tt;

int main() {
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        while (tt && x <= stk[tt]) tt--;
        cout << (tt ? stk[tt] : -1) << ' ';
        stk[++tt] = x;
    }
    return 0;
}