# [第 239 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-239/)

::: details 个人成绩
$RANK: 454 / 3905$

$SCORE: 7$

$TIME: 0:17:01$
:::

## 1.[到目标元素的最小距离](https://leetcode-cn.com/problems/minimum-distance-to-the-target-element/)

模拟

```cpp
class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                ans = min(ans, abs(i - start));
            }
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 2.[将字符串拆分为递减的连续值](https://leetcode-cn.com/problems/splitting-a-string-into-descending-consecutive-values/)

### 回溯

```js
/**
 * @param {string} s
 * @return {boolean}
 */
var splitString = function(s) {
  s = s.split('')
  const n = s.length
  const tk = []
  const dfs = (idx) => {
    if (idx >= n) {
      if (tk.length <= 1) return false
      for (let i = 0; i < tk.length - 1; ++i) {
        if (tk[i] - tk[i + 1] != 1) return false
      }
      return true
    }
    for (let i = idx + 1; i <= n; ++i) {
      tk.push(+s.slice(idx, i).join(''))
      if (dfs(i)) return true
      tk.pop()
    }
    return false
  }
  return dfs(0)
}
```

- 时间复杂度 $\mathcal{O(|S|*2^{|S|})}$;
- 空间复杂度 $\mathcal{O(|S|)}$;

## 3.[邻位交换的最小次数](https://leetcode-cn.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/)

排列 + 贪心

```cpp
class Solution {
public:
    int getMinSwaps(string num, int k) {
        string t(num);
        while (k--) {
            next_permutation(t.begin(), t.end());
        }
        int ans = 0;
        for (int i = 0; i < t.size(); ++i) {
          if (num[i] != t[i]) {
                int j = i + 1;
                while (num[j] != t[i]) ++j;
                for (; j > i; --j) {
                    swap(num[j], num[j - 1]);
                    ++ans;
                }
            }
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(n^2)}$;
- 空间复杂度 $\mathcal{O(n)}$;

## 4.[包含每个查询的最小区间](https://leetcode-cn.com/problems/minimum-interval-to-include-each-query/)