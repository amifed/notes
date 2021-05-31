# [第 52 场双周赛题解](https://leetcode-cn.com/contest/biweekly-contest-52/)

::: details 个人成绩
$RANK: 265 / 3069$

$SCORE: 12$

$TIME: 0:35:04$
:::

## 1.[长度为三且各字符不同的子字符串](https://leetcode-cn.com/problems/substrings-of-size-three-with-distinct-characters/)

遍历

```cpp
class Solution {
public:
    int countGoodSubstrings(string s) {
        int ans = 0;
        for (int i = 0; i + 2 < s.size(); ++i) {
            if (s[i] != s[i + 1]  && s[i + 1] != s[i + 2] && s[i] != s[i + 2]) ans++;
        }
        return ans;
    }
};
```

```ts
function countGoodSubstrings(s: string): number {
    let ans = 0;
    for (let i = 0; i + 2 < s.length; ++i) {
        if (s[i] !== s[i + 1] && s[i + 1] !== s[i + 2] && s[i + 2] !== s[i]) {
            ++ans;
        }
    }
    return ans;
};
```

- 时间复杂度 $\mathcal{O}(n)$
- 空间复杂度 $\mathcal{O}(1)$

## 2.[数组中最大数对和的最小值](https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/)

排序 + 贪心

```cpp
class Solution {
public:
    int minPairSum(vector<int>& a) {
        int n = a.size();
        sort(a.begin(), a.end());
        int ans = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            ans = max(ans, a[i] + a[j]);
        }
        return ans;
    }
};
```

```ts
function minPairSum(nums: number[]): number {
    let ans = 0;
    nums.sort((a, b) => a - b);
    for (let i = 0, j = nums.length - 1; i < j; ++i, --j) {
        ans = Math.max(ans, nums[i] + nums[j]);
    }
    return ans;
};
```

- 时间复杂度 $\mathcal{O}(n\log n)$
- 空间复杂度 $\mathcal{O}(1)$

## 3.[矩阵中最大的三个菱形和](https://leetcode-cn.com/problems/get-biggest-three-rhombus-sums-in-a-grid/)

枚举

```cpp
class Solution {
public:
    int calc(vector<vector<int>>& g, int x, int y, int k) {
        int ans = 0;
        for (int i = 0; i < k; ++i) {
            ans += g[x - i][y + i];
            ans += g[x + i][y + i];
            ans += g[x - k + i][y + k + i];
            ans += g[x + k - i][y + k + i];
        }
        return ans - g[x][y] + g[x][y + k * 2];
    }
    vector<int> getBiggestThree(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        priority_queue<int> pq;
        unordered_set<int> st;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (st.find(g[i][j]) == st.end()) {
                    pq.push(g[i][j]); st.insert(g[i][j]);
                }
                for (int k = 1; i + k < m && j + 2 * k < n && i - k >= 0; ++k) {
                    int t = calc(g, i, j, k);
                    if (st.find(t) == st.end()) {
                        pq.push(t); st.insert(t);
                    }
                }
            }
        }
        vector<int> ans;
        for (int i = 0; i < 3; ++i) {
            if (pq.size()) {
                ans.push_back(pq.top());
                pq.pop();
            }
        }
        return ans;
    }
};
```

```ts
function getBiggestThree(grid: number[][]): number[] {
    const calc = (x: number, y: number, k: number): number => {
        let sum = 0;
        for (let i = 0; i < k; ++i) {
            sum += grid[x - i][y + i];
            sum += grid[x + k - i][y + k + i];
            sum += grid[x + i][y + i];
            sum += grid[x - k + i][y + k + i];
        }
        return sum - grid[x][y] + grid[x][y + 2 * k];
    }
    const m = grid.length, n = grid[0].length;
    const ans: number[] = [];
    const set: Set<number> = new Set();
    for (let i = 0; i < m; ++i) {
        for (let j = 0; j < n; ++j) {
            if (!set.has(grid[i][j])) {
                set.add(grid[i][j]);
                ans.push(grid[i][j]);
            }
            for (let k = 1; i - k >= 0 && i + k < m && j + 2 * k < n; ++k) {
                let t = calc(i, j, k);
                if (!set.has(t)) {
                    set.add(t);
                    ans.push(t);
                }
            }
        }
    }
    return ans.sort((a, b) => b - a).slice(0, 3);
};
```

## 4.[两个数组最小的异或值之和](https://leetcode-cn.com/problems/minimum-xor-sum-of-two-arrays/)

状态压缩 DP

