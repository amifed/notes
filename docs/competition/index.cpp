#include <iostream>
using namespace std;

int n;
int main() {
    cin >> n;
    for (int x = 0; x < 1 << n; ++x) {
        for (int i = 0; i < n; ++i) {
            if (x & 1 << i) cout << i+1 << ' ';
        }
        cout << endl;
    }
    return 0;
}