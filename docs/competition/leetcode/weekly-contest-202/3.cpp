#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findLatestStep(vector<int> &arr, int m) {
        int n = arr.size();
        if (n == m)
            return n;
        set<int> st;
        st.insert(0);
        st.insert(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            auto it = st.upper_bound(arr[i]);
            int left = *prev(it);
            int right = *it;
            if (arr[i] - left - 1 == m || right - arr[i] - 1 == m)
                return i;
            st.emplace(arr[i]);
        }
        return -1;
    }
    int findLatestStep(vector<int> &arr, int m) {
        int n = arr.size();
        if (n == m)
            return n;
        vector<int> v(n + 1, 0);
        int cnt = 0, ans = -1;
        for (int i = 0; i < n; i++) {
            int idx = arr[i];
            v[idx] = idx;
            int l = arr[idx - 1] ? arr[idx - 1] : idx;
            int r = arr[idx - 1] ? arr[idx - 1] : idx;
            cnt -= idx - l == m;
            cnt -= r - idx == m;
            cnt += r - l + 1 == m;
            v[l] = r;
            v[r] = l;
            if (cnt > 0) {
                ans = i + 1;
            }
        }
        return ans;
    }
};