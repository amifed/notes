/** 法一
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 107;
int n, m, g[N][N], vt[N][N];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j) 
            scanf("%d", &g[i][j]);
    queue<pair<int, int>> q;
    q.push({0, 0});
    vt[0][0] = 1;
    int ans = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto p = q.front();
            q.pop();
            if (p.first == n - 1 && p.second == m - 1) {
                printf("%d", ans);
                return 0;
            }
            for (int i = 0; i < 4; ++i) {
                int x = p.first + dx[i], y = p.second + dy[i];
                if (0 <= x && x < n && 0 <= y && y < m && !vt[x][y] && g[x][y] == 0) {
                    q.push({x, y});
                    vt[x][y] = 1;
                }
            }
        }
        ans++;
    }
    return 0;
}
**/

/** 法二 **/
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 107;

int n, m, g[N][N], d[N][N];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int bfs() {
    queue<pair<int, int>> q;
    q.push({0, 0});
    d[0][0] = 0;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = p.first + dx[i], y = p.second + dy[i];
            if (0 <= x && x < n && 0 <= y && y < m && d[x][y] == -1 && g[x][y] == 0) {
                d[x][y] = d[p.first][p.second] + 1;
                q.push({x, y});
            }
        }
    }
    return d[n - 1][m - 1];
}
int main() {
    scanf("%d%d", &n, &m);
    memset(d, -1, sizeof d);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &g[i][j]);
    printf("%d", bfs());
    return 0;
}