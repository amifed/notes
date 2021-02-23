#include <iostream>
#include <cstring>
using namespace std;
const int N = 17;

int d[N], f[N];

int main() {
    memset(f, 0x3f, sizeof f);
    
    d[1] = 1;
    for (int i = 2; i <= 12; ++i) {
        d[i] = 1 + d[i - 1] * 2;
    }
    
    f[0] = 0;
    for (int n = 1; n <= 12; ++n) {
        for (int i = 0; i < n; ++i) {
            f[n] = min(f[n], f[i] * 2 +  d[n - i]);
        }
    }
    for (int i = 1; i <= 12; ++i) cout << f[i] << endl;
    return 0;
}