#include <iostream>
using namespace std;

const int N = 2e5 + 7, INF = 0x3f3f3f3f;
int t, n, a[N], dp[N][2];
int main() {
    scanf("%d", &t);
    while (t--) {
        memset(dp, 0x3f, sizeof dp);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        // 0 firend kill, 1 you kill
        dp[0][1] = 0, dp[1][0] = a[1];
        for (int i = 2; i <= n; ++i) {
            dp[i][0] = min(dp[i - 1][1] + a[i], dp[i - 2][1] + a[i] + a[i - 1]);
            dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
        }
        printf("%d\n", min(dp[n][0], dp[n][1]));
    }
    return 0;
}