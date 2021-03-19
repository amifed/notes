#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using PII = pair<int, int>;

const int N = 1e4 + 7;
int n, m;
struct cmp {
    bool operator()(const PII &a, const PII &b) {
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    }
};

int main() {
    cin >> n >> m;
    priority_queue<PII, vector<PII>, cmp> pq;
    for (int i = 0; i < n; ++i) {
        int v, w;
        cin >> v >> w;
        pq.push({v + w * 2, i});
    }
    for (int i = 0; i < m; ++i) {
        auto p = pq.top(); pq.pop();
        cout << p.second << endl;
    }
    return 0;
}
