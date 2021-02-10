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
#define x first
#define y second
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
    int s2i(string s) {
        int ans = 0;
        for (auto c : s) ans = ans * 10 + (c - '0');
        return ans;
    }
    int calculate(string s) {
        s.push_back(')');
        int n = s.size();
        stack<int> stn, sto;
        sto.push('(');
        for (int i = 0; i < n; ++i) {
            if ('0' <= s[i] && s[i] <= '9') {
                int t = i;
                while (t < n && '0' <= s[t] && s[t] <= '9') ++t;
                // cout << s.substr(i, t - i) << endl;
                stn.push(s2i(s.substr(i, t - i)));
                i = t - 1;
            } else if (s[i] == '(') {
                sto.push(s[i]);
            } else if (s[i] == '+' || s[i] == '-') {
                
            } else if (s[i] == ')') {
                while (!sto.empty() && sto.top() != '(') {
                    int a = stn.top(); stn.pop();
                    int o = sto.top(); sto.pop();
                    int b = stn.top(); stn.pop();
                    cout << b << char(o) << a << endl;
                    stn.push(o == '+' ? b + a : b - a);
                }
            }
        }
        return stn.top();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Solution().calculate( " 2-1 + 2 ");
    
    return 0;
}