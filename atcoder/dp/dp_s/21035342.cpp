#pragma region template
// clang-format off
// #include <bits/stdc++.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

using ll = long long;

const int INF = INT_MAX / 2;
const ll LINF = LLONG_MAX / 2;
const int MOD = 1e9 + 7;
const int ASCII_0 = 48;
const int ASCII_a = 97;

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
template<class T>void printvec(const vector<T>& v) { for (T i : v) cout << i << " "; cout << endl;}

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11) << boolalpha; }; } pre_exec_t;
// clang-format on
#pragma endregion

int main() {
    string K_;
    cin >> K_;
    int N = K_.size();
    vector<int> K(N);
    for (int i : irange(N)) K[i] = K_[i] - ASCII_0;
    int D;
    cin >> D;

    vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(D, vector<ll>(2)));
    dp[0][0][0] = 1;

    for (int i : irange(N)) {
        for (int j : irange(D)) {
            dp[i][j][0] %= MOD;
            dp[i][j][1] %= MOD;
            for (int dig : irange(10)) {
                dp[i + 1][(j + dig) % D][1] += dp[i][j][1];
            }
            for (int dig : irange(K[i])) {
                dp[i + 1][(j + dig) % D][1] += dp[i][j][0];
            }
            dp[i + 1][(j + K[i]) % D][0] += dp[i][j][0];
        }
    }
    int ans = (dp[N][0][0] + dp[N][0][1] - 1 + MOD) % MOD;
    cout << ans << endl;
    return 0;
}
