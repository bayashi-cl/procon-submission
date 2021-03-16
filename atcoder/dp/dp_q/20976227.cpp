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
template<class T>void printvec(const vector<T>& v) { for (T i : v) cout << i << " "; cout << endl;}

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11) << boolalpha; }; } pre_exec_t;
// clang-format on
#pragma endregion

void set_value(vector<ll>& bit, int idx, ll value) {
    idx++;
    int bit_size = (int)bit.size();
    while (idx < bit_size) {
        chmax(bit[idx], value);
        idx += idx & -idx;
    }
}

ll get_max(vector<ll>& bit, int idx) {
    ll res = 0;
    idx++;
    while (idx) {
        chmax(res, bit[idx]);
        idx -= idx & -idx;
    }
    return res;
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> h(N);
    vector<ll> a(N), dp(N);
    for (int i = 0; i < N; i++) {
        int hi;
        cin >> hi;
        h[i] = make_pair(hi, i);
    }
    sort(h.begin(), h.end());
    for (auto&& i : a) cin >> i;

    ll ans = 0;
    vector<ll> bit(N + 1);

    for (auto&& f : h) {
        int i = f.second;
        dp[i] = a[i];
        dp[i] = get_max(bit, i - 1) + a[i];
        set_value(bit, i, dp[i]);
        chmax(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
