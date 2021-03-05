#include <bits/stdc++.h>
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

using ll = long long;
using P = pair<ll, ll>;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N;
    cin >> N;
    vector<double> p(N);
    for (auto&& i : p) cin >> i;
    vector<vector<double>> dp(N, vector<double>(N + 1));
    dp[0][0] = 1 - p[0];
    dp[0][1] = p[0];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            if (j != 0) dp[i][j] += dp[i - 1][j - 1] * p[i];
            dp[i][j] += dp[i - 1][j] * (1 - p[i]);
        }
    }
    double ans = 0;
    for (int i = N; i > N / 2; i--) ans += dp[N - 1][i];
    cout << fixed << setprecision(11) << ans << endl;
    return 0;
}
