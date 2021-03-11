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
const int MOD = 1e9 + 7;

struct pre_exec {
    pre_exec() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} pre_exec_t;
#pragma endregion

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&& i : a) cin >> i;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    for (auto&& w : irange(1, n + 1)) {
        for (auto&& l : irange(n - w + 1)) {
            int r = l + w;
            if (w % 2 == n % 2) {
                dp[l][r] = max(dp[l + 1][r] + a[l], dp[l][r - 1] + a[r - 1]);
            } else {
                dp[l][r] = min(dp[l + 1][r] - a[l], dp[l][r - 1] - a[r - 1]);
            }
        }
    }

    cout << dp[0][n] << endl;
    return 0;
}
