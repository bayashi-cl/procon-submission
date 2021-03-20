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
    int N;
    cin >> N;
    vector<vector<int>> a(N, vector<int>(N));
    for (auto&& i : a) {
        for (auto&& j : i) {
            cin >> j;
        }
    }
    vector<ll> score(1 << N);
    for (int s : irange(1 << N)) {
        for (int i : irange(N - 1)) {
            for (int j : irange(i + 1, N)) {
                if ((s >> i) % 2 == 0 || (s >> j) % 2 == 0) continue;
                score[s] += a[i][j];
            }
        }
    }
    vector<ll> dp(1 << N);
    for (int s : irange(1, 1 << N)) {
        for (int t = s; t > 0; t = (t - 1) & s) {
            chmax(dp[s], dp[s - t] + score[t]);
        }
    }
    cout << dp.back() << endl;
    return 0;
}
