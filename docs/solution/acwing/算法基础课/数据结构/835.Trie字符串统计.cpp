#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int son[N][26], cnt[N], idx;
char str[N];

void insert(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int q = str[i] - 'a';
        if (!son[p][q]) son[p][q] = ++idx;
        p = son[p][q];
    }
    ++cnt[p];
}

int query(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int q = str[i] - 'a';
        if (!son[p][q]) return 0;
        p = son[p][q];
    }
    return cnt[p];
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char op[2];
        scanf("%s%s", op, str);
        if (op[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
    return 0;
}