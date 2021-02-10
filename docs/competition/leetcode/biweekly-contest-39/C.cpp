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
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 1e5 + 7;

class Solution {
public:
    int minimumJumps(vector<int>& f, int a, int b, int x) {
        unordered_set<int> st;
        for (auto &x : f) st.insert(x);
        queue<pair<int, int>> q;
        // 0 向前， 1 向后
        q.emplace(1, 0);
        int ans = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [f, t] = q.front();
                q.pop();
                cout << t << ' ';
                if (t == x) return ans;
                if (st.find(t) != st.end()) continue;
                if (t + a - b <= x) q.emplace(1, t + a);
                if (f == 1 && t - b >= 0) q.emplace(0, t - b);
            }
            ans++;
        }
        return -1;
    }
};
/*
[162,118,178,152,167,100,40,74,199,186,26,73,200,127,30,124,193,84,184,36,103,149,153,9,54,154,133,95,45,198,79,157,64,122,59,71,48,177,82,35,14,176,16,108,111,6,168,31,134,164,136,72,98]
29
98
80
*/
/*
121
*/