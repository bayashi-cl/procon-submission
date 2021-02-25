#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int main() {
    int N;
    cin >> N;
    int dp[110000][3], u[3];
    for (int j = 0; j < 3; j++) {
        cin >> dp[0][j];
    }

    for (int i = 1; i < N; i++) {
        int u[3];
        for (int j = 0; j < 3; j++) {
            cin >> u[j];
        }
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (j != k) {
                    dp[i][k] = max(dp[i][k], dp[i - 1][j] + u[k]);
                }
            }
        }
    }
    int ans = max(max(dp[N - 1][0], dp[N - 1][1]), dp[N - 1][2]);
    cout << ans << endl;
    return 0;
}