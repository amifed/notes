#include <iostream>
using namespace std;
const int N = 17, M = 1e4;

int h;
int val[N], nex[N], idx;
void init() {
    h = 0, idx = 0;
}
void add(int x) {
    val[idx] = x, nex[idx] = h, h = idx++; 
}

int main() {
    init();
    add(3), add(5), add(7);
    for (int i = h; i != -1; i = nex[i]) {
        cout << val[i];
    }
    return 0;
}