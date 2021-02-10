#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 7;

class Solution {
public:
    int dfs(vector<int> &hs, int i, int b, int l) {
        if (i >= hs.size() - 1) return i;
        if (hs[i + 1] <= hs[i]) return dfs(hs, i + 1, b, l);
        int t = hs[i + 1] - hs[i];
        if (t > b && l > 0) return dfs(hs, i + 1, b, l - 1);
        else if (t > b && l <= 0) return i;
        else if (t < b && l <= 0) return dfs(hs, i + 1, b - t, l);
        else return max(dfs(hs, i + 1, b - t, l), dfs(hs, i + 1, b, l - 1));
    }
    int furthestBuilding(vector<int>& hs, int bs, int ls) {
        return dfs(hs, 0, bs, ls);
    }
};