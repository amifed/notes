#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 7;

int n, a[N], s[N];

int main() {
    memset(s, 0, sizeof s);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        s[a[i]]++;
        while (s[a[i]] > 1)
            s[a[j++]]--;
        ans = max(ans, i - j + 1);
    }
    printf("%d", ans);
    return 0;
}