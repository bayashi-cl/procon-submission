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

int int_pow(int a, int b) {
    int res = 1;
    for (int i = 0; i < b; i++) res *= a;
    return res;
}
void solve() {
    auto [k, n] = input<int, 2>();
    vector<pair<Vec, string>> vw;
    for (int i = 0; i < n; i++) {
        auto v = input<int>();
        auto w = input<string>();
        Vec dig;
        while (v != 0) {
            dig.push_back(v % 10);
            v /= 10;
        }
        std::reverse(std::begin(dig), std::end(dig));
        vw.push_back({dig, w});
    }

    for (int s_ = 0; s_ < (pow(3, k)); s_++) {
        int s = s_;
        vector<int> len(k + 1, 1);
        for (int d = k - 1; d >= 0; --d) {
            len[d + 1] += s / int_pow(3, d);
            s %= int_pow(3, d);
        }
        map<int, string> goro;
        bool flg = true;

        for (auto [dig, w] : vw) {
            int l = 0;
            for (auto&& d : dig) l += len[d];
            if (l != (int)w.size()) {
                flg = false;
                break;
            }

            int pos = 0;
            for (auto&& d : dig) {
                string st = w.substr(pos, len[d]);
                if (goro.find(d) == goro.end()) {
                    goro[d] = st;
                } else {
                    if (st != goro[d]) {
                        flg = false;
                        break;
                    }
                }
                pos += len[d];
            }
        }
        if (flg) {
            for (auto [key, value] : goro) print(value);
            break;
        }
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
