#include <iostream>
#include <cstring>
using namespace std;

const int N = 7;
int n;
char p[N][N], g[N][N];
const int dx[] = {-1, 0, 1, 0, 0}, dy[] = {0, 1, 0, -1, 0};

int hash() {
    int ans = 0;
    for (int i = 0, k = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j, ++k) {
            if (g[i][j] == '1') ans += 1 << k;
        }
    }
    return ans;
}

int main() {
    printf("%d", (int)pow(2, 25));
    // scanf("%d", &n);
    // while (n--) {
    //     for (int i = 0; i < 5; ++i) scanf("%s", p[i]);
    // }
    return 0;
}