#pragma region template
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
const ll MOD = 1e9 + 7;

struct pre_exec {
    pre_exec() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} pre_exec_t;
#pragma endregion

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto&& i : a) cin >> i;
    vector<vector<ll>> dp(n, vector<ll>(k + 1));
    for (auto&& i : irange(a[0] + 1)) dp[0][i] = 1;

    for (auto&& i : irange(1, n)) {
        ll s = 0;
        for (auto&& j : irange(k + 1)) {
            if (j - a[i] > 0) s -= dp[i - 1][j - a[i] - 1];
            s += dp[i - 1][j];
            s %= MOD;
            dp[i][j] = s;
        }
    }
    ll ans = dp[n - 1][k] % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << endl;
    return 0;
}
