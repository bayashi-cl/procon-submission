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
// using mint = atcoder::modint1000000007;
using mint = atcoder::modint998244353;

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
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> S;
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        S.push_back({l, r + 1});
    }
    vector<mint> dp(n + 1);
    vector<mint> range(k);
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (auto&& j : irange(k)) {
            auto [l, r] = S[j];
            if (i - l >= 0) range[j] += dp[i - l];
            if (i - r >= 0) range[j] -= dp[i - r];
        }
        for (auto&& j : range) dp[i] += j;
    }

    cout << dp[n].val() << endl;
    return 0;
}
