#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int main() {
    string s, t;
    cin >> s;
    cin >> t;
    int s_size = s.size();
    int t_size = t.size();
    vector<vector<int>> dp(s_size + 1, vector<int>(t_size + 1));
    for (int i = 1; i <= s_size; i++) {
        for (int j = 1; j <= t_size; j++) {
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    string ans;
    int i = s_size, j = t_size;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else if (dp[i][j] == dp[i][j - 1]) {
            j--;
        } else {
            ans = s[i - 1] + ans;
            i--;
            j--;
        }
    }
    cout << ans << endl;
}