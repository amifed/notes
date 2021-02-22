#include <iostream>
#include <cstring>
using namespace std;

const int N = 7;
int n;
char p[N][N], g[N][N];
const int dx[] = {-1, 0, 1, 0, 0}, dy[] = {0, 1, 0, -1, 0};

void turn(int x, int y) {
    for (int i = 0; i < 5; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (0 <= a && a < 5 && 0 <= b && b < 5) {
            g[a][b] = '0' + !(g[a][b] - '0');
        }
    }
}

int work() {
    int ans = 0x3f3f3f3f;
    for (int x = 0; x < 1 << 5; ++x) {
        int cnt = 0;
        memcpy(g, p, sizeof p);
        
        for (int j = 0; j < 5; ++j) {
            if (x >> j & 1) ++cnt, turn(0, j);
        }
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (g[i][j] == '0') ++cnt, turn(i + 1, j);
            }
        }
        
        bool flag = 1;
        for (int j = 0; j < 5; ++j) {
            if (g[4][j] == '0') flag = 0;
        }
        if (flag) ans = min(ans, cnt);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 5; ++i) scanf("%s", p[i]);
        int ans = work();
        printf("%d\n", ans > 6 ? -1 : ans);
    }
    return 0;
}