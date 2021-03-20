#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using PII = pair<int, int>;

const int N = 1e4 + 7;
int n, m;
struct cmp {
    bool operator()(const PII &a, const PII &b) {
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    }
};

int main() {
    cout << 6 / -132 << endl;
    return 0;
}
