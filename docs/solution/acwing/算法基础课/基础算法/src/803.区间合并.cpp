#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using PII = pair<int, int>;
const int INF = 2e9 + 7;

int n;

vector<PII> merge(vector<PII> &segs) {
    vector<PII> ans;
    sort(segs.begin(), segs.end());
    int st = -INF, ed = -INF;
    for (auto &seg : segs) {
        if (ed < seg.first) {
            if (st != -INF) ans.push_back({st, ed});
            st = seg.first, ed = seg.second;
        } else
            ed = max(ed, seg.second);
    }
    if (st != -INF) ans.push_back({st, ed});
    return ans;
}
int main() {
    cin >> n;
    vector<PII> segs;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        segs.push_back({l, r});
    }
    auto ans = merge(segs);
    cout << ans.size() << endl;
}