#pragma region template
#include <atcoder/modint>
#include <boost/range/irange.hpp>
// #include <bits/stdc++.h>
// #include <cmath>
#include <iomanip>
#include <iostream>
// #include <iterator>
#include <limits>
// #include <map>
// #include <numeric>
// #include <queue>
// #include <set>
// #include <stack>
#include <string>
#include <valarray>
#include <vector>

namespace mine {
using std::cin, std::cout, std::endl, std::vector, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
using Vec = std::vector<int>;
using VecVec = std::vector<std::vector<int>>;
using Pa = std::pair<int, int>;
constexpr int MOD = 1'000'000'007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
#pragma endregion

void main() {
    string s;
    cin >> s;
    int len = s.size();
    vector<vector<mint>> dp(len + 1, vector<mint>(3));  //{a, a...b, a...b...c}
    dp[0] = {0, 0, 0};
    mint cand = 1;
    for (auto&& i : irange(1, len + 1)) {
        if (s[i - 1] == '?') {
            dp[i][0] += dp[i - 1][0] * 3 + cand;
            dp[i][1] += dp[i - 1][1] * 3 + dp[i - 1][0];
            dp[i][2] += dp[i - 1][2] * 3 + dp[i - 1][1];
            cand *= 3;
        } else {
            for (auto&& j : irange(3)) dp[i][j] = dp[i - 1][j];
            if (s[i - 1] == 'A') {
                dp[i][0] += cand;
            } else if (s[i - 1] == 'B') {
                dp[i][1] += dp[i - 1][0];
            } else if (s[i - 1] == 'C') {
                dp[i][2] += dp[i - 1][1];
            }
        }
    }
    print(dp[len][2].val());
}
}  // namespace mine

int main() {
    mine::init();
    mine::main();
    std::cout << std::flush;
    return 0;
}
