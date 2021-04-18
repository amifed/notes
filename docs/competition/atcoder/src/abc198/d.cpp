// Problem: D - Send More Money
// Contest: AtCoder - AtCoder Beginner Contest 198
// URL: https://atcoder.jp/contests/abc198/tasks/abc198_d
// Memory Limit: 1024 MB
// Time Limit: 5000 ms

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
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 17;

char a[N], b[N], c[N];
int num[10] = {0,1,2,3,4,5,6,7,8,9};
int pos[26];
set<char> st;

void add(char s[]) {
	for (int i = 0; s[i]; ++i) st.insert(s[i]);
}
bool check(char s[]) {
	return num[pos[s[0] - 'a']] != 0;
}
LL parse(char s[]) {
	LL ans = 0;
	for (int i = 0; s[i]; ++i) ans = ans * 10 + (num[pos[s[i] - 'a']]);
	return ans;
}
void print(char s[]) {
	for (int i = 0; s[i]; ++i) {
		printf("%d", num[pos[s[i] - 'a']]);
	}
	puts("");
}

int main() {
    scanf("%s%s%s", a, b, c);
    add(a), add(b), add(c);
    if (st.size() >= 11) {
    	puts("UNSOLVABLE");
    	return 0;
    }
	int i = 0;
	for (auto &c: st) {
    	pos[c - 'a'] = i++;
    }
	do {
		if (check(a)&&check(b)&&check(c)&&(parse(a)+parse(b)==parse(c))) {
			print(a);print(b);print(c);
			return 0;
		}
	} while (next_permutation(num, num + 10));
	puts("UNSOLVABLE");
    return 0;
}