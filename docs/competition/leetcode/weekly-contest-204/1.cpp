#include <bits/stdc++.h>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
#define forr(n, s, e) for (int(n) = (s); (n) < (e); (n)++)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const int MAXN = 1e5 + 7;

class Solution {
public:
    bool containsPattern(vector<int> &arr, int m, int k) {
        for (int i = 0; i < arr.size(); i++) {
            int start = i, cnt = 0;
            for (int j = i; j < arr.size() && start < arr.size(); j++) {
                if (arr[j] != arr[start]) break;
                start++;
                if (start - i == m) {
                    start = i;
                    cnt++;
                }
            }
            if (cnt == k) return true;
        }
        return false;
    }
};