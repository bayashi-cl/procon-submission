#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

ll dp[110][110000];

int main() {
    ll N, W;
    cin >> N >> W;
    ll w, v;
    for (int i = 0; i <= W; i++) dp[0][i] = 0;

    for (int i = 1; i <= N; i++) {
        cin >> w >> v;
        for (ll j = 0; j <= W; j++) {
            if (j - w >= 0) {
                dp[i][j] = max(dp[i - 1][j - w] + v, dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[N][W] << endl;
    return 0;
}