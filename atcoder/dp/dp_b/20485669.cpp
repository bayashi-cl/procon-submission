#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int main() {
    int N, K, h[110000], dp[110000];
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> h[i];
        dp[i] = INF;
    }
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K; j++) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
            } else {
                break;
            }
        }
    }
    cout << dp[N - 1] << endl;
}