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
    int getMaxLen(vector<int> &nums) {
        int n = nums.size();
        int zero = -1, neg = 0, ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            neg += nums[i] < 0;
            if (nums[i] == 0) {
                zero = i;
                neg = 0;
                continue;
            }
            if (neg % 2 == 0) {
                ans = max(ans, i - zero);
            }
        }
        zero = n, neg = 0;
        for (int i = n - 1; i >= 0; i--) {
            neg += nums[i] < 0;
            if (nums[i] == 0) {
                zero = i;
                neg = 0;
                continue;
            }
            if (neg % 2 == 0) {
                ans = max(ans, zero - i);
            }
        }
        return ans;
    }
};