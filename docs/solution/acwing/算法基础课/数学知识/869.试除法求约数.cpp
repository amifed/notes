#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> getDivisors(int x) {
    vector<int> ans;
    for (int i = 1; i <= x / i; ++i) {
        if (x % i == 0) {
            ans.push_back(i);
            if (i != x / i) ans.push_back(x / i);
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        auto ans = getDivisors(x);
        for (auto &a : ans)
            printf("%d ", a);
        puts("");
    }
    return 0;
}