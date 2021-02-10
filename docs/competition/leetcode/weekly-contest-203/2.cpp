#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxCoins(vector<int>& p) {
        sort(p.begin(), p.end());
        int ret = 0;
        for (int i = p.size() - 2; i >= int(p.size()) / 3; i -= 2) {
            ret += p[i];
        }
        return ret;
    }
};
