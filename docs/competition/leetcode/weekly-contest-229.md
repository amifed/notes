# [第 229 场周赛题解](https://leetcode-cn.com/contest/weekly-contest-229/)

::: details 个人成绩
$AC: 1,2$

$RANK: 1134 / 3483$

$TIME: 0:15:30$
:::

## 1.[交替合并字符串](https://leetcode-cn.com/problems/merge-strings-alternately/)

双指针

```cpp
class Solution {
public:
    string mergeAlternately(string s, string t) {
        string ans;
        int i = 0, j = 0;
        while (i < s.size() || j < t.size()) {
            ans += i < s.size() ? string(1, s[i]) : "";
            ans += j < t.size() ? string(1, t[j]) : "";
            ++i, ++j;
        }
        return ans;
    }
};
```

- 时间复杂度 $O(N+M)$
- 空间复杂度 $O(N+M)$

## 2.[移动所有球到每个盒子所需的最小操作数](https://leetcode-cn.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/)

### 解法一 暴力

中心扩展，统计 `'1'` 的数目和

#### 写法一

```cpp
class Solution {
public:
    vector<int> minOperations(string b) {
        int n = b.size();
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            int l = 0, r = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (b[j] == '1') l += i - j;
            }
            for (int j = i + 1; j < n; ++j) {
                if (b[j] == '1') r += j - i;
            }
            ans.push_back(l + r);
        }
        return ans;
    }
};
```

#### 写法二

```cpp
class Solution {
public:
    vector<int> minOperations(string b) {
        int n = b.size();
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            int t = 0;
            for (int j = 0; j < n; ++j) {
                if (b[j] == '1') t += abs(j - i);
            }
            ans.push_back(t);
        }
        return ans;
    }
};
```

- 时间复杂度 $O(N^2)$
- 空间复杂度 $O(N)$

#### 解法二 记录

计算所有的 `'1'` 到第一个位置的距离之和为 $s$；
再次遍历时，设第 $i$ 个位置左边 `'1'` 的个数为 $l$，右边 `'1'` 的个数为 $r$，每次移动左边所有的 `'1'` 距离 $i$ 的总和多 $l$，右边所有的 `'1'` 距离 $i$ 的总和少 $r$，即 $s + l - r$;

```cpp
class Solution {
public:
    vector<int> minOperations(string b) {
        int n = b.size();
        vector<int> ans;
        int l = 0, r = 0, s = 0;
        for (int i = 0; i < n; ++i) {
            if (b[i] == '1') ++r, s += i;
        }
        s += r;
        for (int i = 0; i < n; ++i) {
            s = s + l - r;
            ans.push_back(s);
            if (b[i] == '1') ++l, --r;
        }
        return ans;
    }
};
```

- 时间复杂度 $O(N)$
- 空间复杂度 $O(N)$
