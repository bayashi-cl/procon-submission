#include <bits/stdc++.h>
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

using ll = long long;
using P = pair<ll, ll>;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (auto&& row : grid) cin >> row;
    vector<vector<mint>> dp(H, vector<mint>(W));
    dp[0][0] = 1;
    for (auto&& i : irange(1, H)) {
        if (grid[i - 1][0] == '.') {
            dp[i][0] = dp[i - 1][0];
        } else {
            dp[i][0] = 0;
        }
    }
    for (auto&& j : irange(1, W)) {
        if (grid[0][j - 1] == '.') {
            dp[0][j] = dp[0][j - 1];
        } else {
            dp[0][j] = 0;
        }
    }
    for (auto&& i : irange(1, H)) {
        for (auto&& j : irange(1, W)) {
            if (grid[i - 1][j] == '.') {
                dp[i][j] += dp[i - 1][j];
            }
            if (grid[i][j - 1] == '.') {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    cout << dp[H - 1][W - 1].val() << endl;
    return 0;
}
