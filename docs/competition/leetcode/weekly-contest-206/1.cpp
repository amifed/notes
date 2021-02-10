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
    int numSpecial(vector<vector<int>> &m) {
        int ans = 0;
        int r = m.size(), c = m[0].size();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (m[i][j] == 0) continue;
                int z = 0, o = 0;
                for (int k = 0; k < r; k++) {
                    z += m[k][j] == 0;
                }
                for (int k = 0; k < c; k++) {
                    o += m[i][k] == 0;
                }
                if (z == r - 1 && o == c - 1) ans++;
            }
        }
        return ans;
    }
};