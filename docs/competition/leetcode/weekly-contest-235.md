# [第 235 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-235/)

::: details 个人成绩
$RANK: 474 / 4493$

$SCORE: 12$

$TIME: 0:58:19$
:::

## 1.[截断句子](https://leetcode-cn.com/problems/truncate-sentence/)

根据题意模拟实现

```js
/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var truncateSentence = function(s, k) {
  return s
    .split(' ')
    .slice(0, k)
    .join(' ')
}
```

判断空格，每遇到一个空格 k - 1， 当 k 为 0 时，前面的字符串即是结果

```cpp
class Solution {
public:
    string truncateSentence(string s, int k) {
        for (int i = 0; i < s.size(); ++i) {
            k -= s[i] == ' ';
            if (!k) return s.substr(0, i);
        }
        return s;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(n)}$

## 2.[查找用户活跃分钟数](https://leetcode-cn.com/problems/finding-the-users-active-minutes/)

每条日志使用哈希表存储，$key$ 为用户 ID，$value$ 为用户活跃时间的无重复集合；

遍历哈希表，统计不同活跃次数的用户个数

```cpp
class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, unordered_set<int>> mp;
        for (auto &log: logs) {
            mp[log[0]].insert(log[1]);
        }
        vector<int> ans(k, 0);
        for (auto &p: mp) {
            ans[p.second.size() - 1]++;
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$
- 空间复杂度 $\mathcal{O(n)}$

## 3.[绝对差值和](https://leetcode-cn.com/problems/minimum-absolute-sum-difference/)

二分查找

首先求出数组 `nums1` 和 `nums2` 的绝对差值和

拷贝 `nums1` 并排序，遍历数组，替换位置 $i$ 的元素为最接近 $nums2[i]$ 的元素，这里使用二分查找；

```cpp
using LL = long long;
const int MOD = 1e9 + 7;
class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int n = nums1.size();
        LL ret = 0;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = nums1[i];
            ret += abs(nums1[i] - nums2[i]);
        }
        sort(a.begin(), a.end());
        LL ans = ret;
        for (int i = 0; i < n; ++i) {
            int l = 0, r = n - 1;
            while (l < r) {
                int mid = l + r >> 1;
                if (a[mid] >= nums2[i]) r = mid;
                else l = mid + 1;
            }
            ans = min(ans, ret - abs(nums1[i] - nums2[i]) + abs(a[r] - nums2[i]));
            if (r > 0) {
                ans = min(ans, ret - abs(nums1[i] - nums2[i]) + abs(a[r - 1] - nums2[i]));
            }
        }
        return ans % MOD;
    }
};
```

- 时间复杂度 $\mathcal{O(n\log n)}$
- 空间复杂度 $\mathcal{O(n)}$

## 4.[序列中不同最大公约数的数目](https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/)

暴力枚举

对于数组中的每个数 $x$，将其当作约数并枚举其倍数;
如果所有是 x 的倍数的数的最大公约数为 x，则 x 必定是这些数字构成子序列的最大公约数

```cpp
const int N = 2e5 + 7;
int p[N];
class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        memset(p, 0, sizeof p);
        int m = 0;
        for (auto &x: nums) {
            p[x] = 1;
            m = max(m, x);
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i) {
            int g = 0;
            for (int j = i; j <= m && g != i; j += i) {
                if (p[j]) g = __gcd(g, j);
            }
            if (g == i) ++ans;
        }
        return ans;
    }
};
```

