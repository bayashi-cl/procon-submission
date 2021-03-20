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

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
template<class T>void printvec(const vector<T>& v) { for (T i : v) cout << i << " "; cout << endl;}

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11) << boolalpha; }; } pre_exec_t;
// clang-format on
#pragma endregion

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

int main() {
    int N;
    cin >> N;
    string s;
    cin >> s;

    vector<vector<mint>> dp(N, vector<mint>(N));
    vector<mint> dp_sum(N);
    dp[0][0] = 1;
    dp_sum[0] = 1;

    for (int i : irange(1, N)) {
        for (int j : irange(i + 1)) {
            if (s[i - 1] == '<') {
                if (j - 1 >= 0) dp[i][j] = dp_sum[j - 1];
            } else {
                dp[i][j] = dp_sum[i - 1];
                if (j - 1 >= 0) dp[i][j] -= dp_sum[j - 1];
            }
        }
        for (int j : irange(i + 1)) {
            dp_sum[j] = dp[i][j];
            if (j - 1 >= 0) dp_sum[j] += dp_sum[j - 1];
        }
    }
    cout << dp_sum.back().val() << endl;
    return 0;
}
