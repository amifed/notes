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
    double dis(int x1, int y1, int x2, int y2) {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    vector<int> bestCoordinate(vector<vector<int>>& ts, int r) {
        int ans = 0, maxx = 0, a, b;
        for (int i = 0; i <= 50; ++i) {
            for (int j = 0; j <= 50; ++j) {
                int tmp = 0;
                for (auto &t : ts) {
                    auto d = dis(t[0], t[1], i, j);
                    if (d <= r) tmp += (int)floor(t[2] / (1 + d));
                }
                if (tmp > maxx) maxx = tmp, a = i, b = j;
            }
        }
        return {a, b};
    }
};