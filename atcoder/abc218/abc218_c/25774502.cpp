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

VecVec rotate(VecVec& mat) {
    int n = mat.size();
    VecVec res(n, Vec(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[j][n - i - 1] = mat[i][j];
        }
    }
    return res;
}
VecVec cut(VecVec& mat) {
    int n = mat.size();
    int low = -1, col = n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 1) {
                if (low == -1) low = i;
                chmin(col, j);
            }
        }
    }

    VecVec res;
    for (int i = low; i < n; ++i) {
        Vec line;
        for (int j = col; j < n; ++j) {
            line.push_back(mat[i][j]);
        }
        res.push_back(line);
    }
    return res;
}

bool compare(VecVec& s, VecVec& t) {
    size_t min_low = min(s.size(), t.size());
    size_t max_low = max(s.size(), t.size());
    size_t min_col = min(s[0].size(), t[0].size());
    size_t max_col = max(s[0].size(), t[0].size());
    for (size_t i = 0; i < max_low; ++i) {
        for (size_t j = 0; j < max_col; ++j) {
            if (i < min_low && j < min_col) {
                if (s[i][j] != t[i][j]) return false;
            } else {
                if (0 <= i && i < s.size() && 0 <= j && j < s[0].size()) {
                    if (s[i][j] == 1) return false;
                }
                if (0 <= i && i < t.size() && 0 <= j && j < t[0].size()) {
                    if (t[i][j] == 1) return false;
                }
            }
        }
    }
    return true;
}

void solve() {
    auto n = input<int>();
    auto s_ = input<string>(n);
    auto t_ = input<string>(n);

    VecVec s(n, Vec(n)), t(n, Vec(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s_[i][j] == '#') s[i][j] = 1;
            if (t_[i][j] == '#') t[i][j] = 1;
        }
    }
    auto cutt = cut(t);
    for (int i = 0; i < 4; ++i) {
        auto cuts = cut(s);
        // for (auto&& e : cuts) debug(e);
        // debug("");
        // for (auto&& e : cutt) debug(e);
        // debug("\n");
        if (compare(cuts, cutt)) {
            print("Yes");
            return;
        }
        s = rotate(s);
    }
    print("No");
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
