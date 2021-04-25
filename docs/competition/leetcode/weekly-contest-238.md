# [第 238 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-238/)

::: details 个人成绩
$RANK: 453 / 3977$

$SCORE: 12$

$TIME: 1:18:04$
:::

## 1.[K 进制表示下的各位数字总和](https://leetcode-cn.com/problems/sum-of-digits-in-base-k/)

进制转换求和

```cpp
class Solution {
public:
    int sumBase(int n, int k) {
        int ans = 0;
        while (n) {
            ans += n % k;
            n /= k;
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(\log_kN)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 2.[最高频元素的频数](https://leetcode-cn.com/problems/frequency-of-the-most-frequent-element/)

### 法一：排序 + 前缀和 + 二分

对数组排序后求前缀和，遍历数组，假设当前值为最高频次值，通过二分查找前缀和数组得到最多补 $k$ 的长度（即频次数）；

```cpp
using ll = long long;
class Solution {
public:
    int maxFrequency(vector<int>& a, int k) {
        int n = a.size(), ans = 0;
        sort(a.begin(), a.end());
        vector<ll> s(n + 1);
        for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i - 1];
        for (int i = 1; i <= n; ++i) {
            int l = 1, r = i;
            while (l < r) {
                int mid = l + r >> 1;
                int len = i - mid + 1;
                if (1LL * a[i - 1] * len - (s[i] - s[mid - 1]) <= k) r = mid;
                else l = mid + 1;
            }
            ans = max(ans, i - r + 1);
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(n\log n)}$;
- 空间复杂度 $\mathcal{O(n)}$;

### 法二：双指针

```cpp
using ll = long long;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        ll sum = 0;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            sum += nums[r];
            while (1LL * nums[r] * (r - l + 1) - sum > k) {
                sum -= nums[l];
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
```

## 3.[最高频元素的频数](https://leetcode-cn.com/problems/frequency-of-the-most-frequent-element/)

滑动窗口

```cpp
class Solution {
public:
    string s = "aeiou";
    unordered_map<char, int> pos = {{'a',0},{'e',1},{'i',2},{'o',3},{'u',4}};
    unordered_map<char, int> mp = {{'a',0},{'e',0},{'i',0},{'o',0},{'u',0}};
    bool check(char ch) {
        int i = pos[ch] + 1;
        while (i < 5) {
            if (mp[s[i++]]) return 0;
        }
        return 1;
    }
    int longestBeautifulSubstring(string w) {
        int n = w.size();
        int l = 0, r = 0, ans = 0;
        for (;r < n; ++r) {
            ++mp[w[r]];
            while (!check(w[r])) --mp[w[l++]];
            if (mp['a'] && mp['e'] && mp['i'] && mp['o'] && mp['u']) ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(|S|)}$;
- 空间复杂度 $\mathcal{O(1)}$;
