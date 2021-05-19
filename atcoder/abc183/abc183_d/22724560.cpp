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
    int n, w;
    cin >> n >> w;

    vector<ll> time(220000);

    for (int i = 0; i < n; i++) {
        int s, t, p;
        cin >> s >> t >> p;
        time[s] += p;
        time[t] -= p;
    }

    ll max_use = time[0];
    for (int i = 1; i < 220000; i++) {
        time[i] += time[i - 1];
        chmax(max_use, time[i]);
    }

    if (max_use <= w) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
