#include <iostream>
#include <algorithm>
#define x first
#define y second
using namespace std;
using pii = pair<int, int>;

const int N = 2507;

int c, l;
pii range[N], spf[N];

int main() {
    cin >> c >> l;
    for (int i = 0; i < c; ++i) cin >> range[i].x >> range[i].y;
    for (int i = 0; i < l; ++i) cin >> spf[i].x >> spf[i].y;
    sort(range, range + c);
    sort(spf, spf + l);
    int i = 0, j = 0;
    int ans = 0;
    for (int i = c - 1; i >= 0; --i) {
        int maxx = 0, idx;
        for (int j = 0; j < l; ++j) {
            if (range[i].x <= spf[j].x && spf[j].x <= range[i].y) {
                if (spf[j].x > maxx && spf[j].y) maxx = spf[j].x, idx = j;
            }
        }
        if (maxx) --spf[idx].y, ++ans;
    }
    cout << ans;
    return 0;
}
