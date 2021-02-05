#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int h, e[N], ne[N], idx;
void init() {
    h = -1, idx = 1;
}
void insert(int x) {
    e[idx] = x, ne[idx] = h, h = idx++;
}
void insert(int k, int x) {
    e[idx] = x, ne[idx] = ne[k], ne[k] = idx++;
}
void remove(int k) {
    ne[k] = ne[ne[k]];
}
int main() {
    int m;
    cin >> m;
    init();
    while (m--) {
        char op;
        int k, x;
        cin >> op;
        if (op == 'H') {
            cin >> x;
            insert(x);
        } else if (op == 'D') {
            cin >> k;
            if (!k) h = ne[h];
            remove(k);
        } else {
            cin >> k >> x;
            insert(k, x);
        }  
    }
    for (int i = h; i != -1; i = ne[i]) cout << e[i] << ' ';

    return 0;

}