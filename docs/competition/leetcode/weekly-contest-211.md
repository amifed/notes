# [第 211 场周赛]

## [A]
```cpp
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int ans = -1;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) ans = max(ans, j - i - 1);
            }
        }
        return ans;
    }
};
```

## [B]
```cpp
class Solution {
public:
    int n;
    unordered_set<string> ust;
    string ans;
    void dfs(string s, int a, int b) {
        if (ust.find(s) != ust.end()) return;
        ust.insert(s);
        if (s < ans) ans = s;
        dfs(s.substr(n - b, b) + s.substr(0, n - b), a, b);
        for (int i = 0; i < n; ++i) {
            if (i & 1) s[i] = (s[i] - '0' + a) % 10 + '0';
        }
        dfs(s, a, b);
    }
    string findLexSmallestString(string s, int a, int b) {
        ans = s, n = s.size();
        dfs(s, a, b);
        return ans;
    }
};
```

## [C]
```cpp
const int N = 1e3 + 7;
int dp[N];
class Solution {
public:
    int bestTeamScore(vector<int>& ss, vector<int>& as) {
        vector<vector<int>> v;
        int n = ss.size();
        for (int i = 0; i < n; ++i) v.push_back({as[i], ss[i]});
        sort(v.begin(), v.end());
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = v[i][1];
            for (int j = 0; j < i; ++j) {
                if (v[j][1] <= v[i][1])
                    dp[i] = max(dp[i], dp[j] + v[i][1]);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

## [D]
```cpp
const int N = 1e4 + 7;
int p[N];
int find(int x) {
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}
class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        for (int i = 1; i <= n; ++i) p[i] = i;
        for (int z = threshold + 1; z <= n; ++z) {
            for (int a = z, b = z + z; b <= n; a += z, b += z) 
                p[find(a)] = find(b);
        }
        vector<bool> ans;
        for (auto &v : queries) {
            ans.push_back(find(v[0]) == find(v[1]));
        }
        return ans;
    }
};
```