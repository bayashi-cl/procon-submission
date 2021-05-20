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

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

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

int main() {
    int s;
    cin >> s;
    int h = s / 3;
    vector<vector<mint>> dp(h + 1, vector<mint>(s + 1));
    for (int j = 3; j <= s; j++) dp[1][j] = 1;

    for (int i = 2; i <= h; i++) {
        mint jsum = 0;
        for (int j = 0; j <= s; j++) {
            if (j - 3 >= 0) jsum += dp[i - 1][j - 3];
            dp[i][j] = jsum;
            if (j >= 3) dp[i][j] += 1;
        }
    }
    cout << dp[h][s].val() << endl;
    return 0;
}
