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
    int h[110000];
    ll dp[110000];
    for (int i = 0; i < N; i++) {
        cin >> h[i];
    }
    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);
    for (int i = 2; i < N; i++) {
        dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]),
                    dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    cout << dp[N - 1] << endl;
}