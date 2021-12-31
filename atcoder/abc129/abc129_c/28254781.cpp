#line 2 "/home/bayashi/dev/byslib/acl/acl.hpp"
#include <iostream>
#include <atcoder/math>
#include <atcoder/modint>

namespace bys {
using atcoder::pow_mod, atcoder::inv_mod;
using mint = atcoder::modint998244353;
using mint7 = atcoder::modint1000000007;
template <int MOD>
inline std::istream& operator>>(std::istream& is, atcoder::static_modint<MOD>& m) {
    long long int n;
    is >> n;
    m = n;
    return is;
}
template <int MOD>
inline std::ostream& operator<<(std::ostream& os, const atcoder::static_modint<MOD>& m) {
    return os << m.val();
}
}  // namespace bys
#line 2 "/home/bayashi/dev/byslib/core/stdlib.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <iomanip>
#line 13 "/home/bayashi/dev/byslib/core/stdlib.hpp"
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
using Pall = pair<ll, ll>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/const.hpp"

namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/io.hpp"

namespace bys {
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
    static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    if (container.empty()) return os;
    std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
//! @brief 任意の型を1つ
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
//! @brief 任意の型がn要素のvector
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
//! @brief 任意の型がn行m列のvector
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
    cin >> res;
    return res;
}

//! @brief 任意の型をN個 受け取りは構造化束縛で
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
//! @brief 2つ以上の異なる型 受け取りは構造化束縛で
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}
//! @brief 標準入力から代入
template <class... Ts>
void cinto(Ts&... args) {
    (cin >> ... >> args);
}
//! @brief pythonのprintっぽい挙動をする
struct Print {
    std::ostream& os;
    string sep = " ", end = "\n";
    Print(std::ostream& os) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T>
    void operator()(const T& a) {
        os << a << end;
    }
    //! @brief 空白区切りで出力
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
    //! @brief 出力後flush インタラクティブ問題用
    template <class... Ts>
    void send(const Ts&... a) {
        operator()(a...);
        os << std::flush;
    }
} print(std::cout), debug(std::cerr);

//! @brief cin高速化など
inline void fastio() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/macro.hpp"

// clang-format off
#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...) debug("[debug] line:", __LINE__, "\t", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
#line 3 "/home/bayashi/dev/byslib/core/solver.hpp"

namespace bys {
struct Solver {
    int IT = 1;
    Solver() { fastio(); }
    void solve();
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys
#line 2 "/home/bayashi/dev/byslib/utility/range.hpp"

namespace bys {
//! @brief pythonのrangeと同じ挙動
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1) : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
    Range(T stop) : it(0), stop(stop), step(1), dir(1) {}
    Range<T> begin() const { return *this; }
    T end() const { return stop; }
    bool operator!=(const T val) const { return (val - it) * dir > 0; }
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
}  // namespace bys
#line 4 "abc129_c/main.cpp"

namespace bys {
void Solver::solve() {
    auto [n, m] = input<int, 2>();
    auto a = input<int>(m);
    set<int> ban(a.begin(), a.end());
    vector<mint7> dp(n + 1);
    dp[0] = 1;
    for (int i : Range(1, n + 1)) {
        if (ban.find(i) != ban.end()) continue;
        dp[i] += dp[i - 1];
        if (i - 2 >= 0) dp[i] += dp[i - 2];
    }
    print(dp.back());
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
