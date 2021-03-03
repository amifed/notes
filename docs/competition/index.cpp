#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 10;
int f[N][N][2];
class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        memset(f, 0, sizeof f);
        int m = seats.size(), n = seats[0].size();
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (seats[i - 1][j - 1] != '.') continue;
                f[i][j][0] = max({f[i - 1][j - 1][1], f[i - 1][j + 1][1], f[i][j - 1][1]});
                f[i][j][1] = max({f[i - 1][j - 1][0], f[i - 1][j + 1][0], f[i][j - 1][0]}) + 1;
            }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max({ans, f[m][i][0], f[m][i][1]});
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    vector<vector<char>> s = {{'#', '.', '#', '#', '.', '#'},
                              {'.', '#', '#', '#', '#', '.'},
                              {'#', '.', '#', '#', '.', '#'}};
    cout << Solution().maxStudents(s) << endl;
    return 0;
}
