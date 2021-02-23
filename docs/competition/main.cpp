#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e5 + 7;
const int INF = 0x3f3f3f3f;

int n;
int p[N], dp[N];

// 最优子结构
// 无后续性
// 重复子问题

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; ++i) cin >> p[i];
        dp[0] = p[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1] + p[i], p[i]);
        }
        cout << *max_element(dp, dp + n) << endl;
    }
    return 0;
}
// 背包问题
// 线性 DP
// 区间 DP
// 计数 DP
// 状态压缩 DP
// 树形 DP
// 记忆化搜索
