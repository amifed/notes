#include <iostream>
#include <queue>
#include <vector>
#define x first
#define y second
using namespace std;
using PII = pair<int, int>;

const int N = 207, M = 37;
PII a[N], b[N], c[N];
int n, q, k;

struct cmp {
    bool operator()(const PII &a, const PII &b) {
        return 1.0 * a.y / a.x < 1.0 * b.y < b.x;
    }
};

int main() {
    priority_queue<PII, vector<PII>, cmp> pq;
    scanf("%d%d%d", &n, &q, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
        pq.emplace(a[i].x, a[i].y);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &b[i].x, &b[i].y);
    }
    int sum = 0, ep = 0;
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        if (sum + p.x > k) continue;
        sum += p.x;
        ep += p.y; 
    }
    for (int i = q - 1; i >= 0; --i) {
        if (sum >= b[i].x) {
            sum -= b[i].y;
            break;
        }
    }
    printf("%d %d", sum, ep);
    return 0;
}
