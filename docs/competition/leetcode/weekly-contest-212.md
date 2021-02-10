# [第 212 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-212/)

## [A. 按键持续时间最长的键]()

```cpp
class Solution {
public:
    char slowestKey(vector<int>& rs, string ks) {
        int maxx = rs[0], n = rs.size();
        char ans = ks[0];
        for (int i = 1; i < n; ++i) {
            if (rs[i] - rs[i - 1] > maxx) {
                maxx = max(maxx, rs[i] - rs[i - 1]);
                ans = ks[i];
            } else if (rs[i] - rs[i - 1] == maxx && ans < ks[i])
                ans = ks[i];
        }
        return ans;
    }
};
```

## [B. 等差子数组]()

```cpp
const int N = 507;
int tmp[N];
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l,
                                          vector<int> &r) {
        vector<bool> ans;
        int n = nums.size(), m = l.size();
        for (int i = 0; i < m; ++i) {
            int k = 0;
            for (int j = l[i]; j <= r[i]; ++j)
                tmp[k++] = nums[j];
            sort(tmp, tmp + k);
            bool flag = 1;
            for (int j = 1; j < k; ++j) {
                if (tmp[j] - tmp[j - 1] != tmp[1] - tmp[0]) {
                    flag = false;
                    break;
                }
            }
            ans.push_back(flag);
        }
        return ans;
    }
};
```

## [C. 最小体力消耗路径](https://leetcode-cn.com/problems/path-with-minimum-effort/)

### 解法一：Dijkstra

使用堆优化的Dijkstra求最短路径，路径长度数组维护的是路径中相邻结点 **高度差绝对值** 的 **最大值**。

```cpp
const int N = 107;
int d[N][N], vt[N][N];
struct node {
    int x, y, z;
    node(int _x, int _y, int _z) : x(_x), y(_y), z(_z){};
    bool operator<(const node &a) const { return z > a.z; }
};

class Solution {
    const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

public:
    int minimumEffortPath(vector<vector<int>> &hs) {
        memset(d, 0x3f, sizeof d);
        memset(vt, 0, sizeof vt);
        int n = hs.size(), m = hs[0].size();
        priority_queue<node> pq;
        d[0][0] = 0;
        pq.emplace(0, 0, 0);
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();
            int x = p.x, y = p.y, z = p.z;
            if (vt[x][y]) continue;
            vt[x][y] = 1;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                    int nz = max(z, abs(hs[nx][ny] - hs[x][y]));
                    if (d[nx][ny] > nz) d[nx][ny] = nz, pq.emplace(nx, ny, nz);
                }
            }
        }
        return d[n - 1][m - 1];
    }
};
```

### 解法二：Binary Search + BFS

通过二分查找结果，使用 BFS 验证。

```cpp
#include <queue>
#include <vector>
using namespace std;
const int N = 107;
int vt[N][N];
int m, n;

class Solution {
    const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

public:
    // binary search + bfs
    bool check(vector<vector<int>> &hs, int limit) {
        memset(vt, 0, sizeof vt);
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        vt[0][0] = 1;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            if (x == m - 1 && y == n - 1) return 1;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = dy[i] + y;
                if (0 <= nx && nx < m && 0 <= ny && ny < n && !vt[nx][ny]) {
                    if (abs(hs[nx][ny] - hs[x][y]) <= limit) {
                        q.emplace(nx, ny);
                        vt[nx][ny] = 1;
                    }
                }
            }
        }
        return 0;
    }
    int minimumEffortPath(vector<vector<int>> &hs) {
        m = hs.size(), n = hs[0].size();
        int l = 0, r = 1e6 + 7;
        while (l < r) {
            int mid = l + r >> 1;
            if (check(hs, mid))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};
```

### 解法三：Union Find





