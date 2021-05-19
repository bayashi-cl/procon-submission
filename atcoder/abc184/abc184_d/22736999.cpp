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

using d3 = vector<vector<vector<double>>>;
using b3 = vector<vector<vector<bool>>>;

double dp(int a, int b, int c, d3& memo, b3& seen) {
    if (a == 100 || b == 100 || c == 100) return 0.0;
    if (seen[a][b][c]) return memo[a][b][c];
    double res = 0.0;
    double abc = a + b + c;
    res += (dp(a + 1, b, c, memo, seen) + 1) * a / abc;
    res += (dp(a, b + 1, c, memo, seen) + 1) * b / abc;
    res += (dp(a, b, c + 1, memo, seen) + 1) * c / abc;

    memo[a][b][c] = res;
    seen[a][b][c] = true;

    return res;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    d3 memo(101, vector<vector<double>>(101, vector<double>(101)));
    b3 seen(101, vector<vector<bool>>(101, vector<bool>(101)));

    auto ans = dp(a, b, c, memo, seen);
    cout << ans << endl;

    return 0;
}
