#pragma region template
#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
// #include <bits/stdc++.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <valarray>
#include <vector>

namespace mine {
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
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
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
#pragma endregion

void main() {
    int n, k;
    cin >> n >> k;
    int kk = k * 2;
    VecVec black(4 * k + 1, Vec(4 * k + 1));
    VecVec white(4 * k + 1, Vec(4 * k + 1));
    for (int i = 0; i < n; i++) {
        int x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'B') {
            black[x % kk + 1][y % kk + 1]++;
            black[x % kk + kk + 1][y % kk + 1]++;
            black[x % kk + 1][y % kk + kk + 1]++;
            black[x % kk + kk + 1][y % kk + kk + 1]++;
        } else {
            white[x % kk + 1][y % kk + 1]++;
            white[x % kk + kk + 1][y % kk + 1]++;
            white[x % kk + 1][y % kk + kk + 1]++;
            white[x % kk + kk + 1][y % kk + kk + 1]++;
        }
    }
    for (auto&& i : irange(1, 4 * k + 1)) {
        for (auto&& j : irange(1, 4 * k + 1)) {
            black[i][j] += black[i][j - 1];
            white[i][j] += white[i][j - 1];
        }
    }
    for (auto&& i : irange(1, 4 * k + 1)) {
        for (auto&& j : irange(1, 4 * k + 1)) {
            black[i][j] += black[i - 1][j];
            white[i][j] += white[i - 1][j];
        }
    }

    int ans = 0;
    for (auto&& i : irange(kk)) {
        for (auto&& j : irange(kk)) {
            int b1 = black[i + k][j + k] + black[i][j] - black[i + k][j] -
                     black[i][j + k];
            int b2 = black[i + kk][j + kk] + black[i + k][j + k] -
                     black[i + k][j + kk] - black[i + kk][j + k];

            int w1 = white[i + kk][j + k] + white[i + k][j] - white[i + kk][j] -
                     white[i + k][j + k];
            int w2 = white[i + k][j + kk] + white[i][j + k] - white[i][j + kk] -
                     white[i + k][j + k];

            chmax(ans, b1 + b2 + w1 + w2);
        }
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
