#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5 + 7;

int n, m;
vector<int> all;
int p[3*N];
int a[N], b[N], c[N];

int find(int x) {
    int l = 0, r = all.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (all[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all.push_back(a[i]);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        all.push_back(b[i]);
    }
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
        all.push_back(c[i]);
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (int i = 0; i < n; ++i) {
        ++p[find(a[i])];
    }
    int maxb = 0;
    for (int i = 0; i < m; ++i) {
        maxb = max(maxb, p[find(b[i])]);
    }
    int maxc = 0, ans = -1;
    for (int i = 0; i < m; ++i) {
        int idx = find(c[i]);
        if (p[find(b[i])] == maxb && p[idx] > maxc) maxc = p[idx], ans = i + 1; 
    }
    cout << ans;
    return 0;
}