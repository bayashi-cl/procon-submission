/**
 * @file core.hpp
 * @author bayashi_cl
 * @brief core/all
 *
 * C++ library for competitive programming by bayashi_cl
 * Repository: https://github.com/bayashi-cl/byslib
 * Document  : https://bayashi-cl.github.io/byslib/
 */
#ifndef LOCAL
#define NDEBUG
#endif
/**
 * @file stdlib.hpp
 * @brief STL Template
 */
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
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
using Pall = pair<ll, ll>;
using ibool = std::int8_t;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;
}  // namespace bys
/**
 * @file const.hpp
 * @brief Const
 */
namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
/**
 * @file types.hpp
 * @brief Types
 *
 * type_traits拡張
 */
namespace bys {
template <class, class = void>
struct has_lshift_to_ostream : std::false_type {};
template <class T>
struct has_lshift_to_ostream<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T&>())>> : std::true_type {};

template <class, class = void>
struct has_rshift_from_istream : std::false_type {};
template <class T>
struct has_rshift_from_istream<T, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>())>> : std::true_type {};

template <class T, class = void>
struct has_tuple_interface : std::false_type {};
template <class T>
struct has_tuple_interface<T, std::void_t<decltype(std::tuple_size<T>())>> : std::true_type {};

template <class, class = void>
struct has_iterator : std::false_type {};
template <class T>
struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

struct Int1 {};
}  // namespace bys
/**
 * @file printer.hpp
 * @brief Output
 */
namespace bys {
class Printer {
    std::ostream& os;
    std::string _sep = " ", _end = "\n";
    template <std::size_t I, class T>
    inline void print_tuple_element(T&& elem) {
        if constexpr (I != 0) cat(_sep);
        cat(std::forward<T>(elem));
    }
    template <class Tp, std::size_t... I>
    inline void print_tuple(Tp&& tp, std::index_sequence<I...>) {
        (print_tuple_element<I>(std::forward<decltype(std::get<I>(tp))>(std::get<I>(tp))), ...);
    }

   public:
    Printer(std::ostream& os_) : os(os_) {}
    ~Printer() { os << std::flush; }

    template <class T>
    void cat(T&& v) {
        if constexpr (has_lshift_to_ostream<std::decay_t<T>>::value) {
            os << v;
        } else if constexpr (has_iterator<std::decay_t<T>>::value) {
            string sep2;
            if constexpr (has_iterator<std::decay_t<typename std::decay_t<T>::value_type>>::value) {
                sep2 = _end;
            } else {
                sep2 = _sep;
            }
            for (auto &&itr = std::begin(v), end = std::end(v); itr != end; ++itr) {
                cat(*itr);
                if (std::next(itr) != end) cat(sep2);
            }
        } else if constexpr (has_tuple_interface<std::decay_t<T>>::value) {
            print_tuple(std::forward<T>(v), std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>());
        } else {
            static_assert([] { return false; }(), "type error");
        }
    }
    void print() { cat(_end); }
    template <class T>
    void print(T&& top) {
        cat(std::forward<T>(top));
        cat(_end);
    }
    template <class T, class... Ts>
    void print(T&& top, Ts&&... args) {
        cat(std::forward<T>(top));
        cat(_sep);
        print(std::forward<Ts>(args)...);
    }
    //! @brief 空白区切りで出力
    template <class... Ts>
    void operator()(Ts&&... args) {
        print(std::forward<Ts>(args)...);
    }

    void flush() { os << std::flush; }
    //! @brief 出力後にflush
    template <class... Ts>
    void send(Ts&&... args) {
        print(std::forward<Ts>(args)...);
        flush();
    }

    //! @brief 区切り文字と終端文字を設定
    Printer set(string sep_ = " ", string end_ = "\n") {
        _sep = sep_;
        _end = end_;
        return *this;
    }
    void lf() { cat(_end); }
};
}  // namespace bys
/**
 * @file scanner.hpp
 * @brief Input
 */
namespace bys {
class Scanner {
    std::istream& is;
    template <class Tp, std::size_t... I>
    inline decltype(auto) read_tuple(std::index_sequence<I...>) {
        return Tp{read<typename std::tuple_element_t<I, Tp>>()...};
    }

   public:
    Scanner(std::istream& is_) : is(is_){};

    template <class... Ts>
    void scan(Ts&... args) {
        (is >> ... >> args);
    }

    /**
     * @brief 2つ以上の異なる型
     *
     * 受け取りは構造化束縛で
     */
    template <class T, class... Us>
    decltype(auto) read() {
        if constexpr (sizeof...(Us) == 0) {
            if constexpr (has_rshift_from_istream<T>::value) {
                T res;
                is >> res;
                return res;
            } else if constexpr (has_tuple_interface<T>::value) {
                auto res = read_tuple<T>(std::make_index_sequence<std::tuple_size_v<T>>());
                return res;
            } else if constexpr (std::is_same_v<T, Int1>) {
                int res;
                is >> res;
                --res;
                return res;
            } else if constexpr (has_iterator<T>::value) {
                //! TODO: 一行読んでsplit
                static_assert([] { return false; }(), "NotImplementedError");
            } else {
                static_assert([] { return false; }(), "TypeError");
            }
        } else {
            return std::tuple{read<T>(), read<Us>()...};
        }
    }
    /**
     * @brief 型TをN個
     *
     * 受け取りは構造化束縛で
     */
    template <class T, std::size_t N, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    std::array<R, N> read() {
        std::array<R, N> res;
        for (auto&& e : res) e = read<T>();
        return res;
    }
    //! @brief n要素のvector
    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<R> readvec(int n) {
        vector<R> res(n);
        for (auto&& e : res) e = read<T>();
        return res;
    }
    //! @brief n*m要素の2次元vector
    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<vector<R>> readvec(int n, int m) {
        vector<vector<R>> res(n);
        for (auto&& e : res) e = readvec<T>(m);
        return res;
    }

    /**
     * @brief 1行を読み取りそれを要素ごとに変換
     * @param f 文字列からの変換関数
     * @param sep 区切り文字
     */
    template <class Lambda = std::function<int(std::string)>,
              typename T = std::invoke_result_t<std::decay_t<Lambda>, std::string>>
    std::vector<T> readln(
        Lambda f = [](string x) { return std::stoi(x); }, char sep = ' ') {
        std::ws(is);
        std::string elem;
        std::getline(is, elem);
        std::stringstream ss{elem};
        std::vector<T> res;
        while (std::getline(ss, elem, sep)) res.emplace_back(f(elem));
        return res;
    }
    /**
     * @brief 1行を文字列で取得
     * @param skip_ws 先頭の空白・改行を読み飛ばす
     */
    std::string getline(bool skip_ws = true) {
        if (skip_ws) std::ws(is);
        std::string res;
        std::getline(is, res);
        return res;
    }
};
}  // namespace bys
/**
 * @file io.hpp
 * @brief I/O
 */
namespace bys {
__attribute__((constructor)) void setup_io() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(11);
    std::cerr << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

Printer print(std::cout), debug(std::cerr);
Scanner scanner(std::cin);
}  // namespace bys
/**
 * @file macro.hpp
 * @brief Macro
 */
// clang-format off
#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...) { std::cerr << "[debug] line" << std::setw(4) << __LINE__ << ": "; debug(__VA_ARGS__); }
#else
#define DEBUG(...)
#endif
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
//! @brief [[maybe_unused]]な変数を生成。
#define UV [[maybe_unused]] auto CONCAT(unused_val_, __LINE__)
#define RE std::runtime_error("line: " + std::to_string(__LINE__) + ", func: " + __func__)
// clang-format on
/**
 * @file solver.hpp
 * @brief Solver
 */
namespace bys {
struct Solver {
    int IT = 1;
    Solver() {}
    void solve();
    //! @brief マルチテストケース用
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys
// -------------------------------------
/**
 * @file bit.hpp
 * @brief Bit
 * @note c++20で<bit>が追加される
 */
namespace bys {
/**
 * @brief bit幅
 *
 * bit_width(x) - 1  < log2(x) <= bit_width(x)
 */
template <class T>
constexpr int bit_width(T x) {
    int bits = 0;
    x = (x < 0) ? (-x) : x;
    for (; x != 0; bits++) x >>= 1;
    return bits;
}
//! @brief 2冪に切り下げ
template <class T>
constexpr T bit_floor(T x) {
    assert(x >= 0);
    return x == 0 ? 0 : T(1) << (bit_width(x) - 1);
}
//! @brief 2冪に切り上げ
template <class T>
constexpr T bit_ceil(T x) {
    assert(x >= 0);
    return x == 0 ? 1 : T(1) << bit_width(x - 1);
}
//! @brief 2進文字列に変換
template <class T>
std::string bin(T n) {
    assert(n > 0);
    if (n == 0) return "0";
    std::string res;
    while (n > 0) {
        res.push_back(n & 1 ? '1' : '0');
        n >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}
//! @brief d bit目が立っているか
template <class T>
constexpr bool pop(T s, int d) {
    return s & (T(1) << d);
}
}  // namespace bys
/**
 * @file numeric.hpp
 * @brief Numeric
 *
 * 数値計算詰め合わせ
 */
namespace bys {
//! @brief 整数の累乗
constexpr ll int_pow(int a, int b) {
    ll res = 1;
    for (int i = 0; i < b; ++i) res *= a;
    return res;
}
/**
 * @brief 繰り返し二乗法
 *
 * O(log q)
 */
template <class T>
constexpr T mod_pow(T p, T q, T mod) {
    T res = 1 % mod;
    p %= mod;
    for (; q; q >>= 1) {
        if (q & 1) res = res * p % mod;
        p = p * p % mod;
    }
    return res;
}
//! @brief ceil(x / y)
template <class T>
constexpr T ceildiv(T x, T y) {
    if ((x < T(0)) ^ (y < T(0))) {
        return x / y;
    } else {
        return (x + y + (x < T(0) ? 1 : -1)) / y;
    }
}
//! @brief floor(x / y)
template <class T>
constexpr T floordiv(T x, T y) {
    if ((x < T(0)) ^ (y < T(0))) {
        return (x - y + (x < T(0) ? 1 : -1)) / y;
    } else {
        return x / y;
    }
}
/**
 * @brief Python::divmod
 *
 * See: https://docs.python.org/ja/3/library/functions.html#divmod
 */
template <class T>
constexpr std::pair<T, T> divmod(T x, T y) {
    auto q = floordiv(x, y);
    return {q, x - q * y};
}

/**
 * @brief Python::%
 *
 * See: https://docs.python.org/ja/3/reference/expressions.html#index-68
 */
template <class T, class S>
constexpr T floormod(T x, S mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

constexpr ll isqrt_aux(ll c, ll n) {
    if (c == 0) return 1;
    ll k = (c - 1) / 2;
    ll a = isqrt_aux(c / 2, n >> (2 * k + 2));
    return (a << k) + (n >> (k + 2)) / a;
}
/**
 * @brief Python::math.isqrt
 *
 * floor(sqrt(n))
 * See: https://docs.python.org/ja/3/library/math.html#math.isqrt
 */
template <class T>
constexpr T isqrt(T n) {
    assert(n >= 0);
    if (n == T(0)) return T(0);
    ll a = isqrt_aux((bit_width(n) - 1) / 2, n);
    return n < a * a ? a - 1 : a;
}
/**
 * @brief Nim::math::almostEqual
 *
 * See: https://nim-lang.org/docs/math.html#almostEqual,T,T,Natural
 */
template <class T, typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
constexpr bool isclose(T x, T y, T coef = 4.0) {
    if (x == y) return true;
    auto diff = std::abs(x - y);
    return diff <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * coef || diff < std::numeric_limits<T>::min();
}

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = floormod(a, b);
    if (a == 0) return {b, 0};
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
}  // namespace bys
/**
 * @file binary_search.hpp
 * @brief Binary Search
 *
 * 二分探索法
 */
namespace bys {
/**
 * @brief 抽象化めぐる式二分探索
 *
 * See: https://twitter.com/meguru_comp/status/697008509376835584
 *
 * @param ok is_okがTrueとなる初期値
 * @param ng is_okがFalseとなる初期値
 * @param is_ok 判定用関数
 * @param args is_okに追加で渡される引数 可変長
 * @return T is_okを満たす最大/小の整数
 */
template <typename T, class Lambda, class... Args>
T meguru_bisect(T ok, T ng, Lambda is_ok, Args... args) {
    static_assert(std::is_same_v<std::invoke_result_t<Lambda, T, Args...>, bool>, "The function signature is invalid.");
    assert(is_ok(ok, args...));
    assert(!is_ok(ng, args...));

    while (std::abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        if (is_ok(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

/**
 * @brief 実数範囲の二分探索
 *
 * @param ok is_okがTrueとなる初期値
 * @param ng is_okがFalseとなる初期値
 * @param rep 繰り返し回数 100回程度?
 * @param is_ok 判定用関数
 * @param args is_okに追加で渡される引数 可変長
 * @return double is_okを満たす最大/小の実数
 */
template <class Lambda, class... Args>
ld bisect_float(ld ok, ld ng, int rep, Lambda is_ok, Args... args) {
    static_assert(std::is_same_v<std::invoke_result_t<Lambda, ld, Args...>, bool>, "The function signature is invalid.");
    assert(is_ok(ok, args...));
    assert(!is_ok(ng, args...));

    for (int i = 0; i < rep; i++) {
        ld mid = (ok + ng) / 2;
        if (is_ok(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}
}  // namespace bys
/**
 * @file change.hpp
 * @brief chmin/chmax
 */
namespace bys {
/**
 * @brief 最大値で更新
 * @return true 更新されたとき
 */
template <class T>
inline bool chmax(T& a, const T& b) {
    return a < b ? a = b, true : false;
}
/**
 * @brief 最小値で更新
 * @return true 更新されたとき
 */
template <class T>
inline bool chmin(T& a, const T& b) {
    return a > b ? a = b, true : false;
}
}  // namespace bys
/**
 * @file range.hpp
 * @brief Python::range
 *
 * Python再現シリーズ range編
 * See: https://docs.python.org/ja/3/library/stdtypes.html#range
 */
namespace bys {
template <typename T>
class Range {
    T it;
    const T stop, step;
    const int dir;

   public:
    Range(T start, T stop, T step = 1) : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
    Range(T stop) : it(0), stop(stop), step(1), dir(1) {}
    Range<T> begin() const { return *this; }
    T end() const { return stop; }
    bool operator!=(const T val) const { return (val - it) * dir > 0; }
    void operator++() { it += step; }
    const T& operator*() const { return it; }

    friend Range reversed(const Range& r) {
        auto new_start = (r.stop - r.dir - r.it) / r.step * r.step + r.it;
        return {new_start, r.it - r.dir, -r.step};
    }
};
//! @brief range(stop)
template <class T>
Range<T> irange(T stop) {
    return Range(stop);
}
//! @brief range(start, stop[, step])
template <class T>
Range<T> irange(T start, T stop, T step = 1) {
    return Range(start, stop, step);
}
}  // namespace bys

namespace bys {
void Solver::solve() {
    auto [n, k] = scanner.read<int, ll>();
    auto a = scanner.readvec<ll>(n);
    sort(a.begin(), a.end());

    auto ok = [&](ll x) -> bool {
        ll cnt = 0;
        for (auto ai : a) {
            if (ai == 0) {
                if (x >= 0) cnt += n - 1;
                continue;
            }

            if (ai < 0) {
                auto th = ceildiv(x, ai);
                auto itr = std::lower_bound(a.begin(), a.end(), th);
                cnt += a.end() - itr;
                if (ai >= th) --cnt;
            } else {
                auto th = floordiv(x, ai);
                auto itr = std::upper_bound(a.begin(), a.end(), th);
                cnt += itr - a.begin();
                if (ai <= th) --cnt;
            }
        }
        return cnt / 2 >= k;
    };
    print(meguru_bisect(LINF, -LINF, ok));
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
