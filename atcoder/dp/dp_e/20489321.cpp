#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N, W;
    static int dp[110][110000];
    int w[110], v[110];
    cin >> N >> W;
    for (int j = 1; j < 110000; j++) {
        dp[0][j] = INF;
    }
    for (int i = 1; i <= N; i++) {
        int w, v;
        cin >> w >> v;
        for (int j = 0; j < 110000; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - v >= 0) {
                dp[i][j] = min(dp[i - 1][j - v] + w, dp[i - 1][j]);
            }
        }
    }
    int ans = 0;
    for (int v = 0; v < 110000; v++) {
        if (dp[N][v] <= W) {
            ans = max(ans, v);
        }
    }
    cout << ans << endl;
}