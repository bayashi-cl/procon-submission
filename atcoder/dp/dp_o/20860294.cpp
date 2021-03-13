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

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11); }; } pre_exec_t;
// clang-format on
#pragma endregion

int main() {
    int N;
    cin >> N;
    vector<vector<int>> a(N, vector<int>(N));
    for (auto&& i : a) {
        for (auto&& j : i) cin >> j;
    }

    vector<int> dp(1 << N);
    dp[0] = 1;
    for (int s : irange(1, (1 << N))) {
        int b = __builtin_popcount(s);
        for (int l : irange(N)) {
            if ((s >> l) % 2 == 0) continue;
            dp[s] += dp[s - (1 << l)] * a[b - 1][l];
            dp[s] %= MOD;
        }
    }
    cout << dp[(1 << N) - 1] << endl;
    return 0;
}
