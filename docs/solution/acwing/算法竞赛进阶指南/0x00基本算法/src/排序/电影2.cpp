#include <iostream>
#include <unordered_map>
using namespace std;

const int N = 2e5 + 7;

unordered_map<int, int> mp;
int n, m;
int b[N];

int main() {
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        ++mp[x];
    }
    cin >> m;
    int maxb = 0;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        if (mp[b[i]] > maxb) maxb = mp[b[i]];
    }
    int maxc = 0, ans;
    for (int i = 0; i < m; ++i) {
        cin >> x;
        if (mp[b[i]] == maxb && mp[x] > maxc) maxc = mp[x], ans = i + 1; 
    }
    cout << ans;
    return 0;
}