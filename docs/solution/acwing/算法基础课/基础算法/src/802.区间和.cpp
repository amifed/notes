#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 3e5 + 7;
using PII = pair<int, int>;

int n, m, a[N], s[N];
vector<int> all;
vector<PII> add, query;

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
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int x, c;
        scanf("%d%d", &x, &c);
        all.push_back(x);
        add.push_back({x, c});
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        all.push_back(l);
        all.push_back(r);
        query.push_back({l, r});
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (auto &p : add) {
        int i = find(p.first);
        a[i] += p.second;
    }

    for (int i = 1; i <= all.size(); i++) s[i] = s[i - 1] + a[i];

    for (auto &p : query) {
        int l = find(p.first), r = find(p.second);
        printf("%d\n", s[r] - s[l - 1]);
    }   
    return 0;
}
