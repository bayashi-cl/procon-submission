#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <atcoder/math>
#include <atcoder/modint>
#include <cassert>
#include <cmath>
#include <complex>
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
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace bys {
// clang-format off
using atcoder::pow_mod, atcoder::inv_mod;
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;
using mint = atcoder::modint998244353;
using ll = long long int;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T> using uset = std::unordered_set<T>;
template <class S, class T> using umap = std::unordered_map<S, T>;
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
inline std::istream& operator>>(std::istream& is, mint& m) { ll n; is >> n; m = n; return is; }
inline std::ostream& operator<<(std::ostream& os, const mint& m) { return os << m.val(); }
template <class T, class U> std::istream& operator>>(std::istream& is, std::pair<T, U>& p) { return is >> p.first >> p.second; }
template <typename T, typename U> std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) { return os << p.first << " " << p.second; }
struct is_container_impl { template <typename T> static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{}); template <typename T> static auto check(...) -> std::false_type; };
template <typename T> class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept { std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; }); return os << *std::prev(std::end(container)); }
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) { std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; }); return is; }
template <class T> inline T input() { T n; cin >> n; return n; }
template <class T> inline vector<T> input(int n) { vector<T> res(n); cin >> res; return res; }
template <class T, size_t N> inline std::array<T, N> input() { std::array<T, N> res; cin >> res; return res; }
template <class S, class T, class... Us> std::tuple<S, T, Us...> input() { std::tuple<S, T, Us...> res; std::apply([](auto&... e) { (cin >> ... >> e); }, res); return res; }
struct Print {
    std::ostream& os;
    char sep = ' ', end = '\n';
    Print(std::ostream& os = std::cout) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T> void operator()(const T& a) { os << a << end; }
    template <class T, class... Ts> void operator()(const T& a, const Ts&... b) { os << a; (os << ... << (os << sep, b)); os << end; }
} print, debug(std::cerr);
template <class T> inline bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
template <class T> inline bool chmin(T& a, const T& b) { if (b < a) { a = b; return 1; } return 0; }
template <class T> inline T ceil(T a, T b) { return (a + b - 1) / b; }
inline bool pop(int s, int d) { return s & (1 << d); }
inline void init() { cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11); std::cerr << std::boolalpha; }
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
}  // namespace bys

namespace bys {
template <class T>
struct CumulativeSum2D {
    vector<vector<T>> data;
    CumulativeSum2D(int n, int m) : data(n + 1, vector<T>(m + 1)){};
    CumulativeSum2D(const vector<vector<T>>& v)
        : data(v.size() + 1, vector<T>(v[0].size() + 1)) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            std::copy(v[i].begin(), v[i].end(), std::next(data[i + 1].begin()));
        }
    };
    void set(int i, int j, int x) {
        assert(!build);
        data[i + 1][j + 1] = x;
    }
    void construct() {
        assert(!build);
        int n = data.size();
        int m = data[0].size();
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                data[i][j] +=
                    data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
            }
        }
        build = true;
    }
    // [si, gi), [sj, gj)
    T sum(int si, int sj, int gi, int gj) {
        assert(build);
        return (data[gi][gj] - data[si][gj] - data[gi][sj] + data[si][sj]);
    }

   private:
    bool build = false;
};
void solve() {
    auto [h, w] = input<int, 2>();
    auto [k, v] = input<ll, 2>();
    vector<vector<ll>> a(h);
    for (auto&& ai : a) ai = input<ll>(w);
    CumulativeSum2D cs(a);
    cs.construct();
    ll ans = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int p = i + 1; p <= h; ++p) {
                for (int q = j + 1; q <= w; ++q) {
                    ll area = (p - i) * (q - j);
                    ll ground = cs.sum(i, j, p, q);
                    ll cost = area * k + ground;
                    if (cost <= v) chmax(ans, area);
                }
            }
        }
    }
    print(ans);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    return 0;
}
