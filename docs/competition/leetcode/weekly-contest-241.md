# [第 241 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-241/)

::: details 个人成绩
$RANK: 636 / 4490$

$SCORE: 12$

$TIME: 0:58:39$
:::

## 1.[找出所有子集的异或总和再求和](https://leetcode-cn.com/problems/sum-of-all-subset-xor-totals/)

二进制子集枚举

```cpp
class Solution {
public:
    int subsetXORSum(vector<int>& a) {
        int ans = 0;
        int n = a.size();
        for (int x = 0; x < 1 << n; ++x) {
            int t = 0;
            for (int i = 0; i < n; ++i) {
                if (x >> i & 1) t ^= a[i];
            }
            ans += t;
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(2^n)}$;
- 空间复杂度 $\mathcal{O(1)}$;

## 2.[构成交替字符串需要的最小交换次数](https://leetcode-cn.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/)

模拟，最终结果只会有三种情况:

- `0` 和 `1` 相同
- `0` 比 `1` 多 1
- `0` 比 `1` 少 1

由于交换不仅限于相邻元素，因此只需统计与最终 01 串不符的位置个数，根据情况返回结果

> 如果 0 的个数 大于 1 的个数，最终 01 串只能为 0101...10，相反同理

```cpp
class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        int a = 0, b = 0;
        for (auto &c: s) a += c == '0', b += c == '1';
        if (abs(a - b) > 1) return -1;
        int t1 = 0, t2 = 0;
        for (int i = 0; i < n ; i += 2) {
            t1 += s[i] != '1';
            t2 += s[i] != '0';
        }
        if (a == b) return min(t1, t2);
        else if (a > b) return t2;
        else return t1;
    }
};
```

- 时间复杂度 $\mathcal{O}(|S|)$;
- 空间复杂度 $\mathcal{O}(1)$;

## 3.[找出和为指定值的下标对](https://leetcode-cn.com/problems/finding-pairs-with-a-certain-sum/)

哈希表 + 暴力统计

```cpp
class FindSumPairs {
public:
    vector<int> a, b;
    unordered_map<int, int> mp;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        a = nums1, b = nums2;
        for (int &x: nums2) mp[x]++;
    }

    void add(int index, int val) {
        mp[b[index]]--;
        b[index] += val;
        mp[b[index]]++;
    }

    int count(int tot) {
        int ans = 0;
        for (int i = 0; i < a.size(); ++i) {
            ans += mp[tot - a[i]];
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(N + M)}$;
- 空间复杂度 $\mathcal{O(M)}$;

双哈希表

```cpp
class FindSumPairs {
public:
    vector<int> a, b;
    unordered_map<int, int> ma, mb;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        a = nums1, b = nums2;
        for (auto &x: a) ++ma[x];
        for (auto &x: b) ++mb[x];
    }

    void add(int index, int val) {
        mb[b[index]]--;
        if (!mb[b[index]]) mb.erase(b[index]);
        b[index] += val;
        mb[b[index]]++;
    }

    int count(int tot) {
        int ans = 0;
        for (auto &[k, v]: ma) {
            ans += v * mb[tot - k];
        }
        return ans;
    }
};
```

- 时间复杂度 $\mathcal{O(N + M)}$;
- 空间复杂度 $\mathcal{O(N + M)}$;
