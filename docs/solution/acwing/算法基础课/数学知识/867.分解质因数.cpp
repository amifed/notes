#include <iostream>
using namespace std;

int n, x;

void divide(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, ++s;
            printf("%d %d\n", i, s);
        }
    }
    if (x > 1) printf("%d %d\n", x, 1);
    printf("\n");
}

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        divide(x);
    }
    return 0;
}