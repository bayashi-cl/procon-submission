#line 2 "byslib/template/bys.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
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
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;

// alias
using ll = long long int;
using ld = long double;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;

// const
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;

// I/O
// pair
template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
    return is >> p.first >> p.second;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << p.first << " " << p.second;
}

// STL container
struct is_container_impl {
    template <typename T>
    static auto check(T&& obj)
        -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container
    : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    if (container.empty()) return os;
    std::for_each(std::begin(container), std::prev(std::end(container)),
                  [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container),
                  [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
    cin >> res;
    return res;
}
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}

struct Print {
    std::ostream& os;
    char sep = ' ', end = '\n';
    Print() : os(std::cout) {}
    Print(std::ostream& os) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T>
    void operator()(const T& a) {
        os << a << end;
    }
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
} print, debug(std::cerr);

// utility
template <class T>
inline bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline bool chmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline T iceil(T a, T b) {
    return (a + b - 1) / b;
}
inline bool pop(int s, int d) { return s & (1 << d); }
inline bool pop(ll s, int d) { return s & (1LL << d); }

// config
inline void init() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

// macro
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
// clang-format off
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on

// solver
// void solve();
// void solver(int t = 1) {
//     for (int i = 0; i < t; ++i) solve();
// }
struct Solver {
    Solver() { init(); }
    void solve();
    void solve(int rep) {
        for (int i = 0; i < rep; ++i) solve();
    }
};
}  // namespace bys
#line 2 "abc175_e/main.cpp"

namespace bys {
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1)
        : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
    Range(T stop) : it(0), stop(stop), step(1), dir(1) {}
    Range<T> begin() const { return *this; }
    T end() const { return stop; }
    bool operator!=(const T& value) const { return (value - it) * dir > 0; }
    void operator++() { it += step; }
    const T& operator*() const { return it; }

   private:
    T it;
    const T stop, step;
    const int dir;

    friend Range reversed(const Range& r) {
        auto new_start = (r.stop - r.dir - r.it) / r.step * r.step + r.it;
        return {new_start, r.it - r.dir, -r.step};
    }
};
void Solver::solve() {
    auto [r, c, k] = input<int, 3>();
    vector item(r + 1, vector<int>(c + 1));
    for (int i = 0; i < k; ++i) {
        auto [ri, ci, v] = input<int, 3>();
        item[ri][ci] = v;
    }

    vector dp(r + 1, vector(c + 1, vector<ll>(4)));
    for (auto i : Range(1, r + 1)) {
        for (auto j : Range(1, c + 1)) {
            for (auto cnt : Range(4)) {
                chmax(dp[i][j][cnt], dp[i][j - 1][cnt]);
                chmax(dp[i][j][0], dp[i - 1][j][cnt]);
            }
            if (item[i][j] == 0) continue;
            for (auto cnt : reversed(Range(3))) {
                chmax(dp[i][j][cnt + 1], dp[i][j][cnt] + item[i][j]);
            }
        }
    }
    print(*std::max_element(dp[r][c].begin(), dp[r][c].end()));
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
