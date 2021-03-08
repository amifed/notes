#include <iostream>
using namespace std;

void divide(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, ++s;
            printf("%d %d\n", i, s);
        }
    }
    if (x > 1) printf("%d %d\n", x, 1); // 判断是否存在大于 sqrt(x) 的质因子
    printf("\n");
}

int main() {
    divide(18);
    return 0;
}