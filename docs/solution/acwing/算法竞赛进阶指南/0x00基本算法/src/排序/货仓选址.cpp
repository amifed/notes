#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
int a[N];
int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int ans = 0;
    for (int i = 0;i < n; ++i) 
        ans += abs(a[i] - a[n >> 1]);
    cout << ans;
    return 0;
}