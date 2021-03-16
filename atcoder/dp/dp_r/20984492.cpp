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

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
namespace ublas = boost::numeric::ublas;
using mat = ublas::matrix<mint>;

mat mat_pow(mat& adj, ll k) {
    if (k == 0) return ublas::identity_matrix(adj.size1());
    mat res = mat_pow(adj, k / 2);
    res = ublas::prod(res, res);
    if (k % 2 == 1) res = ublas::prod(res, adj);
    return res;
}

int main() {
    ll N, K;
    cin >> N >> K;
    mat adj(N, N, 0);
    for (ll i : irange(N)) {
        for (ll j : irange(N)) {
            int e;
            cin >> e;
            adj(i, j) = e;
        }
    }
    mat dp = mat_pow(adj, K);
    mint ans = 0;
    for (ll i : irange(N)) {
        for (ll j : irange(N)) {
            ans += dp(i, j);
        }
    }
    cout << ans.val() << endl;
    return 0;
}
