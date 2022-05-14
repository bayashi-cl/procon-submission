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
#include <optional>
#include <utility>
/**
 * @file monoid.hpp
 * @brief Monoid
 *
 * モノイド
 */
namespace bys {
template <class T>
struct Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b);
    static constexpr bool commutative{false};
};
template <class T>
struct Add : Magma<T> {
    using typename Magma<T>::set_type;
    static constexpr set_type operation(set_type a, set_type b) { return a + b; }
    static constexpr set_type identity{0};
    static constexpr bool commutative{true};
};
template <class T>
struct Min : Magma<T> {
    using typename Magma<T>::set_type;
    static constexpr set_type operation(set_type a, set_type b) { return std::min(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::max()};
};
template <class T>
struct Max : Magma<T> {
    using typename Magma<T>::set_type;
    static constexpr set_type operation(set_type a, set_type b) { return std::max(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::min()};
};
template <class T>
struct Update : Magma<T> {
    using set_type = std::optional<T>;
    static constexpr set_type operation(set_type a, set_type b) { return b.has_value() ? b : a; }
    static constexpr set_type identity{std::nullopt};
};
template <class T>
struct Affine : Magma<T> {
    using set_type = std::pair<T, T>;
    static constexpr set_type operation(set_type a, set_type b) { return {a.first * b.first, a.second * b.first + b.second}; }
    static constexpr set_type identity{1, 0};
};
}  // namespace bys
/**
 * @file lazy_segment_tree.hpp
 * @brief Lazy Segment Tree
 */
/**
 * @file mapping.hpp
 * @brief Mapping
 *
 * 遅延セグ木 作用素
 */
namespace bys {
template <class T, class ActMonoid>
struct MappingToSet {
    static constexpr void mapping(T&, typename ActMonoid::set_type) {
        static_assert([] { return false; }(), "mapping function does not defined.");
    }
};
template <class T, class S>
struct MappingToSet<T, Add<S>> {
    static constexpr void mapping(T& t, typename Add<S>::set_type u) { t += u; }
};
template <class T, class S>
struct MappingToSet<T, Min<S>> {
    static constexpr void mapping(T& t, typename Min<S>::set_type u) {
        if (t > u) t = u;
    }
};
template <class T, class S>
struct MappingToSet<T, Update<S>> {
    static constexpr void mapping(T& t, typename Update<S>::set_type u) {
        if (u.has_value()) t = u.value();
    }
};
template <class Monoid, class ActMonoid>
struct Mapping {
    static constexpr void mapping(typename Monoid::set_type&, typename ActMonoid::set_type, int) {
        static_assert([] { return false; }(), "mapping function does not defined.");
    }
};
template <class T, class S>
struct Mapping<Min<T>, Update<S>> {
    static constexpr void mapping(typename Min<T>::set_type& t, typename Update<S>::set_type s, int) {
        if (s.has_value()) t = s.value();
    }
};
template <class T, class S>
struct Mapping<Add<T>, Add<S>> {
    static constexpr void mapping(typename Add<T>::set_type& t, typename Add<S>::set_type s, int w) { t += s * w; }
};
template <class T, class S>
struct Mapping<Min<T>, Add<S>> {
    static constexpr void mapping(typename Min<T>::set_type& t, typename Add<S>::set_type s, int) { t += s; }
};
template <class T, class S>
struct Mapping<Add<T>, Update<S>> {
    static constexpr void mapping(typename Add<T>::set_type& t, typename Update<S>::set_type s, int w) {
        if (s.has_value()) t = s.value() * w;
    }
};
template <class T, class S>
struct Mapping<Add<T>, Affine<S>> {
    static constexpr void mapping(typename Add<T>::set_type& t, typename Affine<S>::set_type s, int w) {
        t = t * s.first + w * s.second;
    }
};
template <class T, class S>
struct Mapping<Max<T>, Update<S>> {
    static constexpr void mapping(typename Max<T>::set_type& t, typename Update<S>::set_type s, int) {
        if (s.has_value()) t = s.value();
    }
};
}  // namespace bys
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
namespace bys {
/**
 * @brief 遅延伝播セグメント木
 *
 * 区間更新: O(logN)
 * 区間クエリ: O(logN)
 * 一点取得: O(logN)
 * See: https://ikatakos.com/pot/programming_algorithm/data_structure/segment_tree/lazy_segment_tree
 *
 * @tparam Monoid モノイド
 * @tparam ActMonoid 作用素モノイド
 * @tparam Action 作用関数オブジェクト 区間の幅も渡される
 * @todo 二分探索: O(logN)
 */
template <class Monoid, class ActMonoid, class Action = Mapping<Monoid, ActMonoid>>
class LazySegmentTree {
    using value_type = typename Monoid::set_type;
    using act_type = typename ActMonoid::set_type;
    int _n, n_leaf, logsize;
    std::vector<act_type> lazy;
    std::vector<value_type> data;

    void reload(int p) { data[p] = Monoid::operation(data[p * 2], data[p * 2 + 1]); }
    void push(const int p) {
        int w = n_leaf >> bit_width(p);
        apply_segment(p * 2, lazy[p], w);
        apply_segment(p * 2 + 1, lazy[p], w);
        lazy[p] = ActMonoid::identity;
    }
    void apply_segment(const int p, act_type f, int w) {
        Action::mapping(data[p], f, w);
        if (p < n_leaf) lazy[p] = ActMonoid::operation(lazy[p], f);
    }

   public:
    LazySegmentTree(int n)
        : _n(n),
          n_leaf(bit_ceil(_n)),
          logsize(bit_width(_n - 1)),
          lazy(n_leaf, ActMonoid::identity),
          data(n_leaf * 2, Monoid::identity) {}
    LazySegmentTree(int n, value_type init)
        : _n(n),
          n_leaf(bit_ceil(_n)),
          logsize(bit_width(_n - 1)),
          lazy(n_leaf, ActMonoid::identity),
          data(n_leaf * 2, Monoid::identity) {
        std::fill_n(data.begin() + n_leaf, _n, init);
        for (int i = n_leaf - 1; i > 0; --i) {
            data[i] = Monoid::operation(data[i * 2], data[i * 2 + 1]);
        }
    }
    LazySegmentTree(std::vector<value_type> v)
        : _n(v.size()),
          n_leaf(bit_ceil(_n)),
          logsize(bit_width(_n - 1)),
          lazy(n_leaf, ActMonoid::identity),
          data(n_leaf * 2, Monoid::identity) {
        std::copy(v.begin(), v.end(), data.begin() + n_leaf);
        for (int i = n_leaf - 1; i > 0; --i) {
            data[i] = Monoid::operation(data[i * 2], data[i * 2 + 1]);
        }
    }
    value_type operator[](int p) {
        assert(0 <= p && p < _n);
        p += n_leaf;
        for (int i = logsize; i > 0; --i) push(p >> i);
        return data[p];
    }
    void update(int p, const value_type& x) {
        assert(0 <= p && p < _n);
        p += n_leaf;
        for (int i = logsize; i > 0; --i) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= logsize; ++i) reload(p >> i);
    }
    value_type query(int l, int r) {
        assert(0 <= l);
        assert(l <= r);
        assert(r <= _n);
        if (l == r) return Monoid::identity;

        l += n_leaf;
        r += n_leaf;

        for (int i = logsize; i > 0; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        value_type left = Monoid::identity, right = Monoid::identity;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = Monoid::operation(left, data[l++]);
            if (r & 1) right = Monoid::operation(data[--r], right);
        }
        return Monoid::operation(left, right);
    }

    value_type query_all() { return data[1]; }
    void apply(int i, act_type f) { apply(i, i + 1, f); }

    void apply(int l, int r, act_type f) {
        assert(0 <= l);
        assert(l <= r);
        assert(r <= _n);
        if (l == r) return;
        l += n_leaf;
        r += n_leaf;

        for (int i = logsize; i > 0; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        int w = 1;
        while (l2 < r2) {
            if (l2 & 1) apply_segment(l2++, f, w);
            if (r2 & 1) apply_segment(--r2, f, w);
            l2 >>= 1;
            r2 >>= 1;
            w <<= 1;
        }

        for (int i = 1; i <= logsize; i++) {
            if (((l >> i) << i) != l) reload(l >> i);
            if (((r >> i) << i) != r) reload((r - 1) >> i);
        }
    }
};
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
    auto [n, q] = scanner.read<int, 2>();
    auto a = scanner.readvec<ll>(n);
    LazySegmentTree<Add<ll>, Update<ll>> seg(a);
    for (UV : irange(q)) {
        auto t = scanner.read<int>();
        if (t == 1) {
            auto [i, x] = scanner.read<Int1, int>();
            seg.update(i, x);
        } else {
            auto x = scanner.read<int>();
            seg.apply(0, n, x);
        }
        print(seg.query(0, n));
    }
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
