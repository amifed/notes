#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
int h[N], idx;

void down(int p) {
    int t = p;
    if (p * 2 <= idx && h[p * 2] < h[t]) t = p * 2;
    if (p * 2 + 1 <= idx && h[p * 2 + 1] < h[t]) t = p * 2 + 1;
    if (t != p) {
        swap(h[t], h[p]);
        down(t);
    }
} 

void up(int p) {
    while (p / 2 && h[p / 2] > h[p]) {
        swap(h[p / 2], h[p]);
        p /= 2;
    }
}

