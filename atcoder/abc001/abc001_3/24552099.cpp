#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
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

namespace bys {
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
inline std::istream& operator>>(std::istream& is, mint& m) {ll n; is >> n; m = n; return is;}
inline std::ostream& operator<<(std::ostream& os, const mint& m) { os << m.val(); return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class T> inline T input() {T n; cin >> n; return n;}
template <class T> inline vector<T> input(int n) {vector<T> res(n); for (auto&& r : res) cin >> r; return res;}
template <class T, size_t N> inline std::array<T, N> input() {std::array<T, N> res; for (auto&& r : res) cin >> r; return res;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
}  // namespace bys

namespace bys {
void solve() {
    auto [deg, dis] = input<int, 2>();
    int wind = std::round((double)(dis) / 6);
    deg *= 10;
    string dir;
    if (1125 <= deg && deg < 3375) {
        dir = "NNE";
    } else if (3375 <= deg && deg < 5625) {
        dir = "NE";
    } else if (5625 <= deg && deg < 7875) {
        dir = "ENE";
    } else if (7875 <= deg && deg < 10125) {
        dir = "E";
    } else if (10125 <= deg && deg < 12375) {
        dir = "ESE";
    } else if (12375 <= deg && deg < 14625) {
        dir = "SE";
    } else if (14625 <= deg && deg < 16875) {
        dir = "SSE";
    } else if (16875 <= deg && deg < 19125) {
        dir = "S";
    } else if (19125 <= deg && deg < 21375) {
        dir = "SSW";
    } else if (21375 <= deg && deg < 23625) {
        dir = "SW";
    } else if (23625 <= deg && deg < 25875) {
        dir = "WSW";
    } else if (25875 <= deg && deg < 28125) {
        dir = "W";
    } else if (28125 <= deg && deg < 30375) {
        dir = "WNW";
    } else if (30375 <= deg && deg < 32625) {
        dir = "NW";
    } else if (32625 <= deg && deg < 34875) {
        dir = "NNW";
    } else {
        dir = "N";
    }

    int w;
    if (0 <= wind && wind <= 2) {
        w = 0;
    } else if (3 <= wind && wind <= 15) {
        w = 1;
    } else if (16 <= wind && wind <= 33) {
        w = 2;
    } else if (34 <= wind && wind <= 54) {
        w = 3;
    } else if (55 <= wind && wind <= 79) {
        w = 4;
    } else if (80 <= wind && wind <= 107) {
        w = 5;
    } else if (108 <= wind && wind <= 138) {
        w = 6;
    } else if (139 <= wind && wind <= 171) {
        w = 7;
    } else if (172 <= wind && wind <= 207) {
        w = 8;
    } else if (208 <= wind && wind <= 244) {
        w = 9;
    } else if (245 <= wind && wind <= 284) {
        w = 10;
    } else if (285 <= wind && wind <= 326) {
        w = 11;
    } else if (327) {
        w = 12;
    } else {
        assert(false);
    }
    if (w == 0) dir = "C";
    print(dir, w);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
