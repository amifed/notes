#include <algorithm>
#include <bitset>
#include <iostream>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define x first
#define y second
using namespace std;
const int N = 57;

int g[N][N];
int n = 3, k = 1;
vector<vector<int>> edges = {{1, 2}, {2, 3}, {1, 3}};
int x = 1, y = 3;

int dfs(int u, int t) {
    if (t > k + 1)
        return 0;
    else if (u == y)
        return 1;
    int ans = 0;
    for (auto &v : edges[u]) {
        ans += dfs(v, t + 1);
    }
    return ans;
}

int main() {
    cout << dfs(x, 0) << endl;
    return 0;
}
