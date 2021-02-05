#include <iostream>
using namespace std;
int n;
bool is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i <= x / i; ++i)
        if (x % i == 0) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        if (is_prime(x)) puts("Yes");
        else puts("No");
    }
    return 0;
}