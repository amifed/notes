#include <iostream>
using namespace std;

const int N = 1e6 + 7;
int ps[N], cnt;
bool vt[N];

/**
 *  一般线性筛法
 */
void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) {
            ps[cnt++] = i;
            for (int j = i + i; j <= n; j += i)
                vt[j] = 1;
        }
    }
}

/**
 * 快速线性筛法
 */
void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vt[i]) ps[cnt++] = i;
        for (int j = 0; ps[j] <= n / i; ++j) {
            vt[ps[j] * i] = 1;
            if (i % ps[j] == 0) break;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    get_primes(n);
    printf("%d", cnt);
}