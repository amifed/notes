#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define it insert
#define pob pop_back
#define pub push_back
#define emb emplace_back
#define all(v) (v).begin(), (v).end()
#define mkp(a, b) make_pair(a, b)
using LL = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using PII = pair<int, int>;
using PIL = pair<int, LL>;
using PLL = pair<LL, LL>;

const int N = 17;
int mp[10];

int main() {
    string s;
    cin >> s;
    int n = s.size();
    memset(mp, 0, sizeof mp);
    for (auto &c : s)
        ++mp[c - '0'];
    if (n == 1) {
        printf("%s", s[0] == '8' ? "Yes" : "No");
        return 0;
    }
    if (n == 2) {
        for (int i = 16; i < 100; i += 8) {
            int x = i / 10, y = i % 10;
            --mp[x], --mp[y];
            if (mp[x] >= 0 && mp[y] >= 0) {
                printf("Yes");
                return 0;
            }
            ++mp[x], ++mp[y];
        }
        printf("No");
        return 0;
    }
    for (int i = 104; i < 1000; i += 8) {
        int x = i / 100, y = i / 10 % 10, z = i % 10;
        --mp[x], --mp[y], --mp[z];
        if (mp[x] >= 0 && mp[y] >= 0 && mp[z] >= 0) {
            printf("Yes");
            return 0;
        }
        ++mp[x], ++mp[y], ++mp[z];
    }
    printf("No");
    return 0;
}