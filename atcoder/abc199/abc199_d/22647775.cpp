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
#include <atcoder/dsu>
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    ll ans = 0;
    for (ll i : irange(1 << n)) {
        vector<int> bit(n, 0);
        int n_red = 0;
        for (auto&& d : irange(n)) {
            if ((i & (1 << d)) == 0) continue;
            bit[d] = 1;
            n_red++;
        }

        // 赤が隣接してたらcontinue
        bool flag = false;
        for (auto&& s : irange(n)) {
            if (bit[s]) {
                for (int to : graph[s]) {
                    if (bit[to]) flag = true;
                }
            }
        }
        if (flag) continue;

        atcoder::dsu d(n * 2);
        for (auto&& s : irange(n)) {
            if (!bit[s]) {
                for (int to : graph[s]) {
                    if (bit[to]) continue;
                    d.merge(s, to + n);
                    d.merge(s + n, to);
                }
            }
        }
        // 二部グラフじゃなければcontinue
        flag = false;
        for (auto&& s : irange(n)) {
            if (!bit[s]) {
                if (d.same(s, s + n)) flag = true;
            }
        }
        if (flag) continue;

        int p = ((int)d.groups().size() - n_red * 2) / 2;
        ans += 1 << p;
    }
    cout << ans << endl;
    return 0;
}
