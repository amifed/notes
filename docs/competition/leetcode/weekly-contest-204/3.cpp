#include <bits/stdc++.h>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
#define forr(n, s, e) for (int(n) = (s); (n) < (e); (n)++)
#define rfor(n, s, e) for (int(n) = (s); (n) > (e); (n)--)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e5 + 7;

class Solution {
public:
    int row, col;
    int numIslands(vector<vector<int>> v) {
        int ans = 0;
        forr(i, 0, row) forr(j, 0, col) if (v[i][j] == 1) ans += dfs(v, i, j);
        return ans;
    }
    int dfs(vector<vector<int>> &v, int x, int y) {
        if (x < 0 || x >= row || y < 0 || y >= col || v[x][y] == 0) return 0;
        v[x][y] = 0;
        dfs(v, x + 1, y);
        dfs(v, x - 1, y);
        dfs(v, x, y + 1);
        dfs(v, x, y - 1);
        return 1;
    }
    int minDays(vector<vector<int>> &grid) {
        row = grid.size(), col = grid[0].size();
        int n = numIslands(grid);
        if (n != 1) return 0;
        forr(i, 0, row) {
            forr(j, 0, col) {
                if (grid[i][j] == 0) continue;
                grid[i][j] = 0;
                if (numIslands(grid) != 1) return 1;
                grid[i][j] = 1;
            }
        }
        return 2;
    }
};