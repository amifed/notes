# [第 46 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-46/)

## 1.[最长的美好子字符串](https://leetcode-cn.com/problems/longest-nice-substring/)

暴力搜索

```cpp
class Solution {
public:
    bool check(vector<bool> &a, vector<bool> &b) {
        for (int i = 0; i < 26; ++i) {
            if (a[i] != b[i]) return 0;
        }
        return 1;
    }
    string longestNiceSubstring(string s) {
        int n = s.size();
        string ans = "";
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                vector<bool> a(26, 0), A(26, 0);
                for (int k = i; k <= j; ++k) {
                    if (isupper(s[k])) A[s[k] - 'A'] = 1;
                    else a[s[k] - 'a'] = 1;
                }
                if (check(a, A) && j - i + 1 > ans.size()) ans = s.substr(i, j - i + 1);
            }
        }
        return ans;
    }
};
```

**复杂度分析**
- 时间复杂度 $O(n^3)$
- 空间复杂度 $O(n)$

## 2.[通过连接另一个数组的子数组得到一个数组](https://leetcode-cn.com/problems/form-array-by-concatenating-subarrays-of-another-array/)

模拟，由于子数组不相交且保持相对顺序，使用一个指针在 `nums` 上遍历即可

```cpp
class Solution {
public:
    bool isSub(vector<int> &s, vector<int> &t, int i) {
        int j = 0;
        while (i < s.size() && j < t.size() && s[i] == t[j]) ++i, ++j;
        return j == t.size();
    }
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int cnt = 0;
        for (int i = 0; i < nums.size() && cnt < groups.size(); ++i) {
            if (isSub(nums, groups[cnt], i)) i += groups[cnt].size() - 1, ++cnt;
        }
        return cnt == groups.size();
    }
};
```

**复杂度分析**
- 时间复杂度 $O(mnk)$，$m$ 为 `nums` 数组长度，$n$ 为 `groups` 数组长度，$k$ 为 `groups` 中的数组长度。
- 空间复杂度 $O(1)$。

## 3.[地图中的最高点](https://leetcode-cn.com/problems/map-of-highest-peak/)

多源 BFS 求最短路

```cpp
using PII = pair<int, int>;
class Solution {
    const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        queue<PII> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (g[i][j] == 1) {
                    g[i][j] = 0;
                    q.push({i, j});
                } else g[i][j] = 0x3f3f3f3f;
            }
        }
        while (!q.empty()) {
            auto p = q.front(); q.pop();
            for (int d = 0; d < 4; ++d) {
                int a = p.first + dx[d], b = p.second + dy[d];
                if (0 <= a && a < m && 0 <= b && b < n) {
                    if (g[a][b] > g[p.first][p.second] + 1) {
                        g[a][b] = g[p.first][p.second] + 1;
                        q.push({a, b});
                    }
                }
            }
        }
        return g;
    }
};
```
