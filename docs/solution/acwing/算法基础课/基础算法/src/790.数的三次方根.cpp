#include <iostream>
using namespace std;
const double eps = 1e-8;

int main() {
    double n;
    scanf("%lf", &n);
    double l = 0, r = n;
    if (n < 0) swap(l, r);
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (mid * mid * mid >= n) r = mid;
        else l = mid;
    }
    printf("%lf", l);
}