#include <iostream>
#include <cstring>
using namespace std;

/** 开放定址法
*/
const int N = 2e5 + 7, INF = 0x3f3f3f3f;
int h[N];

int find(int x) {
    int k = (x % N + N) % N;
    while (h[k] != INF && h[k] != x) 
        if (++k == N) k = 0;
    return k;
}

int main() {
    memset(h, 0x3f, sizeof h);
    int n;
    scanf("%d",&n);
    while (n--) {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        int k = find(x);
        if (op[0] == 'I') h[k] = x;
        else {
            if (h[k] != INF) puts("Yes");
            else puts("No");
        }
    }
    
    return 0;
}

/** 拉链法
const int N = 1e5 + 7;
int h[N], e[N], ne[N], idx;

void insert(int x) {
    int k = (x % N + N) % N;
    e[idx] = x, ne[idx] = h[k], h[k] = idx++;
}

bool find(int x) {
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i]) 
        if (e[i] == x) return 1;
    return 0;
}

int main() {
    memset(h, -1, sizeof h);
    int n;
    scanf("%d", &n);
    while (n--) {
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        if (op[0] == 'I') insert(x);
        else {
            if (find(x)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
*/