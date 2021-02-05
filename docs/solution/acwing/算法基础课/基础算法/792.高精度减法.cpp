#include <iostream>
#include <vector>
using namespace std;

// A >= B
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--)
        if (A[i] != B[i]) return A[i] > B[i];
    return true;
}
vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < A.size(); i++) {
        t = A[i] - t; //处理借位
        if (i < B.size()) t -= B[i];
        c.push_back((t + 10) % 10); // t >= 0 || t < 0
        t = t < 0; // 借位
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}
int main() {
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');

    if (cmp(A, B)) {
        auto C = sub(A, B);
        for (int i = C.size() - 1; i >= 0; i--)
            printf("%d", C[i]);

    } else {
        auto C = sub(B, A);
        printf("-");
        for (int i = C.size() - 1; i >= 0; i--)
            printf("%d", C[i]);
    }
}