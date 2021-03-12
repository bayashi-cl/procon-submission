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
    int N;
    cin >> N;
    vector<int> a(N);
    for (auto&& i : a) cin >> i;
    vector<vector<ll>> cost(N, vector<ll>(N + 1));
    for (auto&& l : irange(N)) {
        cost[l][l + 1] = a[l];
        for (auto&& r : irange(l + 2, N + 1)) {
            cost[l][r] = cost[l][r - 1] + a[r - 1];
        }
    }

    vector<vector<ll>> dp(N, vector<ll>(N + 1));
    for (int w : irange(2, N + 1)) {
        for (int l : irange(N - w + 1)) {
            int r = l + w;
            dp[l][r] = LINF;
            for (int m : irange(l + 1, r)) {
                dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + cost[l][r]);
            }
        }
    }
    cout << dp[0][N] << endl;
    return 0;
}
