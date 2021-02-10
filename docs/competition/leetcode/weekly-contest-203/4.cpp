#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int dp[505][505];
    int ps[505];
    int dfs(int l, int r) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        dp[l][r] = 0;
        if (l == r) {
            return dp[l][r];
        }
        for (int i = l; i < r; i++) {
            int sf = ps[i] - ps[l - 1];
            int sb = ps[r] - ps[i];
            if (sf < sb) {
                dp[l][r] = max(dp[l][r], sf + dfs(l, i));
            } else if (sf > sb) {
                dp[l][r] = max(dp[l][r], sb + dfs(i + 1, r));
            } else {
                dp[l][r] = max({dp[l][r], sf + dfs(l, i), sb + dfs(i + 1, r)});
            }
        }
        return dp[l][r];
    }
    int stoneGameV(vector<int> &sv) {
        memset(dp, -1, sizeof(dp));
        ps[0] = 0;
        for (int i = 0; i < sv.size(); i++) {
            ps[i + 1] = ps[i] + sv[i];
        }
        return dfs(1, sv.size());
    }
};