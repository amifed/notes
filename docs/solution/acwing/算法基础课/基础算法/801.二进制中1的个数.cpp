#include <iostream>
using namespace std;

int lowbit(int x) {
    return x & -x;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        int x, ans = 0;
        cin >> x;
        while (x) x -= lowbit(x), ans++;
        cout << ans << ' ';
    }
    return 0;
}