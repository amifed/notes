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
    int unhappyFriends(int n, vector<vector<int>> &pr,
                       vector<vector<int>> &pa) {
        vector<int> f(n);
        for (auto &p : pa)
            f[p[0]] = p[1], f[p[1]] = p[0];
        vector<vector<int>> v(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                v[i][pr[i][j]] = j;
            }
        }
        unordered_set<int> st;
        for (int i = 0; i < n; i++) {
            for (auto &x : pr[i]) {
                if (f[i] == x) break;
                if (v[x][i] > v[x][f[x]]) st.insert(i);
            }
        }
        return st.size();
    }
};