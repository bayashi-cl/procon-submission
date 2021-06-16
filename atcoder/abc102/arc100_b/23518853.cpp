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
// clang-format off
using boost::irange;
using std::cin, std::cout, std::endl, std::vector, std::string, std::min, std::max, std::abs;
using ll = long long int;
using mint = atcoder::modint1000000007;
using Vec = std::vector<int>;
using VecVec = std::vector<std::vector<int>>;
using Pa = std::pair<int, int>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
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
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; print(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
#pragma endregion

void main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    vector<ll> cs(n + 10);
    for (auto&& i : irange(1, n + 1)) cs[i] = cs[i - 1] + a[i - 1];
    int l = 1, r = 3;
    ll ans = LINF;

    // while (c < n - 1) {
    for (int c = 2; c < n - 1; c++) {
        while (l < c) {
            if (abs(cs[l] - (cs[c] - cs[l])) >
                abs(cs[l + 1] - (cs[c] - cs[l + 1]))) {
                l++;
            } else {
                break;
            }
        }
        while (r < n) {
            if (abs((cs[n] - cs[r]) - (cs[r] - cs[c])) >
                abs((cs[n] - cs[r + 1]) - (cs[r + 1] - cs[c]))) {
                r++;
            } else {
                break;
            }
        }
        ll P = cs[l];
        ll Q = cs[c] - cs[l];
        ll R = cs[r] - cs[c];
        ll S = cs[n] - cs[r];
        ll mi = min(min(P, Q), min(R, S));
        ll ma = max(max(P, Q), max(R, S));
        chmin(ans, ma - mi);
    }
    print(ans);
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    std::cout << std::flush;
    return 0;
}
