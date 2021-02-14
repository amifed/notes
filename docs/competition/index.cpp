#include <iostream>
#include <stack>
using namespace std;
const int N = 30;

int n, m;
char s[N];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = i, k = 0; j >= 0; --j, ++k) s[j] = 'A' + k;
        for (int j = i, k = 0; j < m; ++j, ++k) s[j] = 'A' + k;
        for (int j = 0; j < m; ++j) cout << s[j];
        cout << '\n';
    }
    return 0;
}