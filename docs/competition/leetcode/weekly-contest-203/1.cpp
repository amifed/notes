#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
class Solution {
public:
    vector<int> mostVisited(int n, vector<int> &r) {
        int cnt[MAXN];
        memset(cnt, 0, sizeof(int) * MAXN);
        for_each(r.begin(), r.end(), [](int &a) { a--; });
        int idx = 1, pos = r[0], maxx = -1;
        while (idx < r.size()) {
            while (pos != r[idx]) {
                cnt[pos]++;
                maxx = max(maxx, cnt[pos]);
                pos = (pos + 1) % n;
            }
            cnt[pos]++;
            maxx = max(maxx, cnt[pos]);
            pos = (pos + 1) % n;
            idx++;
        }
        vector<int> v;
        for (int i = 0; i <= n; i++) {
            if (cnt[i] == maxx) {
                v.push_back(i + 1);
            }
        }
        return v;
    }
};
