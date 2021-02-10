# [第 210 场周赛]()

## [A]
```cpp
class Solution {
public:
    int maxDepth(string s) {
        stack<char> st;
        int ans = 0;
        for (auto &c : s) {
            if (c == '(') {
                st.push('(');
                ans = max(ans, (int)st.size());
            }
            else if (c == ')') {
                st.pop();
            }
        }
        return ans;
    }
};
```

## [B]
```cpp
const int N = 107;
int g[N][N];
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        memset(g, 0, sizeof g);
        for (auto &v : roads) g[v[0]][v[1]] = g[v[1]][v[0]] = 1;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int tmp = 0;
                for (int k = 0; k < n; ++k) tmp += (g[i][k] == 1);
                for (int k = 0; k < n; ++k) tmp += (g[j][k] == 1);
                ans = max(ans, tmp - g[i][j]);
            }
        } 
        return ans;
    }
};
```

## [C]
```cpp
class Solution {
public:
    bool check(string a, string b) {
        int n = a.size();
        int i, j;
        if (n & 1) i = j = n / 2;
        else i = n / 2 - 1, j = n / 2;
        while (i >= 0 && j < n && a[i] == a[j]) --i, ++j;
        int ti = i, tj = j;
        while (ti >= 0 && j < n && a[ti] == b[tj]) --ti, ++tj;
        if (ti == -1 && tj == n) return true;
        ti = i, tj = j;
        while (ti >= 0 && j < n && b[ti] == a[tj]) --ti, ++tj;
        return ti == -1 && tj == n;
    }
    bool checkPalindromeFormation(string a, string b) {
        return check(a, b) || check(b, a);
    }
};

```