#include <iostream>
using namespace std;

int n;

int main() {
    cin >> n;
    for (int x = 0; x < 1 << n; ++x) {
        for (int i = 0; i < n; ++i) {
            if (x >> i & 1) printf("%d ", i + 1);
        }
        puts("");
    }
    return 0;
}