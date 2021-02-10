# [第 214 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-214/)

### C. 

```cpp
class Solution {
    LL rangeSum(int x, int y) { return 1LL * (x + y) * (y - x + 1) / 2; }

public:
    int maxProfit(vector<int> &a, int os) {
        int n = a.size();
        int l = 0, r = *max_element(a.begin(), a.end());
        while (l < r) {
            int mid = (l + r) >> 1;
            LL t = 0;
            for (auto &x : a)
                t += max(x - mid, 0);
            if (t <= os)
                r = mid;
            else
                l = mid + 1;
        }
        LL t = 0;
        for (auto &x : a)
            t += max(x - l, 0);
        int rest = os - t;
        LL ans = 0;
        for (auto &x : a) {
            if (x >= l) {
                if (rest > 0)
                    ans += rangeSum(l, x), --rest;
                else
                    ans += rangeSum(l + 1, x);
            }
        }
        return ans % MOD;
    }
};
```