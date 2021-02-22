#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int n;
const int dx[] = {-1, 0, 1, 0, 0}, dy[] = {0, 1, 0, -1, 0};
unordered_map<int, int> mp;

int turn(int u, int i) {
    int x = i / 5, y = i % 5;
    for (int d = 0; d < 5; ++d) {
        int a = x + dx[d], b = y + dy[d];
        if (0 <= a && a < 5 && 0 <= b && b < 5) {
            u ^= 1 << (a * 5 + b);
        }
    }
    return u;
}

void bfs() {
    int x = (1 << 25) - 1;
    int cnt = 0;
    mp[x] = 1;
    queue<int> q;
    q.push(x);
    int ma = 0;
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        if (mp[p] > 6) break;
        for (int i = 0; i < 25; ++i) {
            ++cnt;
            int t = turn(p, i);
            if (!mp.count(t)) {
                mp[t] = mp[p] + 1;
                q.push(t);
            }
        }
        ma = max(ma, (int)q.size());
    }
}

int main() {
    bfs();
    scanf("%d", &n);
    while (n--) {
        int x = 0;
        for (int i = 0; i < 25; ++i) {
            int a;
            scanf("%1d", &a);
            x += (a << i);
        }
        printf("%d\n", mp[x] - 1);
    }
    return 0;
}