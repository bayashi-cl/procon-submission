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
    vector<int> cnt(4);
    for (int i = 0; i < N; i++) {
        // for (auto&& i : irange(N)) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    vector<vector<vector<double>>> dp(
        N + 10, vector<vector<double>>(N + 10, vector<double>(N + 10, 0.)));

    for (auto&& i : irange(N + 1)) {
        for (auto&& j : irange(N + 1)) {
            for (auto&& k : irange(N + 1)) {
                int ijk = i + j + k;
                if (ijk == 0) continue;
                dp[i][j][k] = (double)N / ijk;
                if (i - 1 >= 0) dp[i][j][k] += dp[i - 1][j + 1][k] * i / ijk;
                if (j - 1 >= 0) dp[i][j][k] += dp[i][j - 1][k + 1] * j / ijk;
                if (k - 1 >= 0) dp[i][j][k] += dp[i][j][k - 1] * k / ijk;
            }
        }
    }
    cout << dp[cnt[3]][cnt[2]][cnt[1]] << endl;
    return 0;
}
