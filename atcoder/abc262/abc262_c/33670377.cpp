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
struct has_rshift_from_istream : std::false_type {};
template <class T>
struct has_rshift_from_istream<T, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>())>> : std::true_type {};
template <class T>
constexpr bool has_rshift_from_istream_v = has_rshift_from_istream<T>::value;

template <class, class = void>
struct has_lshift_to_ostream : std::false_type {};
template <class T>
struct has_lshift_to_ostream<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T&>())>> : std::true_type {};
template <class T>
constexpr bool has_lshft_to_ostream_v = has_lshift_to_ostream<T>::value;

template <class, class = void>
struct is_tuple_like : std::false_type {};
template <class T>
struct is_tuple_like<T, std::void_t<decltype(std::tuple_size<T>())>> : std::true_type {};
template <class T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

template <class, class = void>
struct is_iterable : std::false_type {};
template <class T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>()))>> : std::true_type {};
template <class T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template <class T>
struct Indexed {
    static_assert(std::is_integral_v<T>);
    using resolve_to = T;
};
using iint = Indexed<int>;
using ill = Indexed<long long int>;

template <class, class = void>
struct is_indexed : std::false_type {};
template <class T>
struct is_indexed<Indexed<T>> : std::true_type {};
template <class T>
constexpr bool is_indexed_v = is_indexed<T>::value;

template <class T, class = void>
struct resolve_type {
    using type = T;
};
template <class T>
struct resolve_type<T, std::void_t<typename T::resolve_to>> {
    using type = typename T::resolve_to;
};
template <class T, std::size_t N>
struct resolve_type<std::array<T, N>> {
    using type = std::array<typename resolve_type<T>::type, N>;
};
template <class T, class U>
struct resolve_type<std::pair<T, U>> {
    using type = std::pair<typename resolve_type<T>::type, typename resolve_type<U>::type>;
};
template <class... Args>
struct resolve_type<std::tuple<Args...>> {
    using type = std::tuple<typename resolve_type<Args>::type...>;
};
template <class T>
using resolve_type_t = typename resolve_type<T>::type;
}  // namespace bys
/**
 * @file printer.hpp
 * @brief Output
 */
namespace bys {
class Printer {
    std::ostream& _os;
    // sep1 "\n"       : iterable<iterable>
    // sep2 " " or "\n": iterable, args
    // sep3 " "        : tuple_like
    std::string sep1 = "\n", sep2 = " ", sep3 = " ", end = "\n";

    template <std::size_t I, class T>
    void print_tuple_element(T&& elem) {
        if constexpr (I != 0) cat(sep3);
        cat(std::forward<T>(elem));
    }
    template <class Tp, std::size_t... I>
    void print_tuple(Tp&& tp, std::index_sequence<I...>) {
        (print_tuple_element<I>(std::forward<std::tuple_element_t<I, std::decay_t<Tp>>>(std::get<I>(tp))), ...);
    }

   public:
    Printer() = delete;
    Printer(std::ostream& os) : _os(os) { os << std::fixed << std::setprecision(11) << std::boolalpha; }
    ~Printer() { _os << std::flush; }

    template <class T>
    void cat(T&& v) {
        if constexpr (has_lshft_to_ostream_v<std::decay_t<T>>) {
            _os << v;
        } else if constexpr (is_iterable_v<std::decay_t<T>>) {
            std::string sep;
            if constexpr (is_iterable_v<typename std::decay_t<T>::value_type>) {
                sep = sep1;
            } else {
                sep = sep2;
            }
            for (auto &&f = std::begin(v), &&itr = std::begin(v), &&t = std::end(v); itr != t; ++itr) {
                if (itr != f) cat(sep);
                cat(*itr);
            }
        } else if constexpr (is_tuple_like_v<std::decay_t<T>>) {
            print_tuple(std::forward<T>(v), std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>());
        } else {
            static_assert([] { return false; }(), "type error");
        }
    }

    void print() { cat(end); }
    template <class T>
    void print(T&& v) {
        cat(std::forward<T>(v));
        cat(end);
    }
    template <class T, class... Ts>
    void print(T&& top, Ts&&... args) {
        cat(std::forward<T>(top));
        cat(sep2);
        print(std::forward<Ts>(args)...);
    }
    template <class... Ts>
    void operator()(Ts&&... args) {
        print(std::forward<Ts>(args)...);
    }

    void flush() { _os << std::flush; }
    template <class... Ts>
    void send(Ts&&... args) {
        print(std::forward<Ts>(args)...);
        flush();
    }

    Printer set_sep(const std::string& sep_1, const std::string& sep_2, const std::string& sep_3) {
        sep1 = sep_1;
        sep2 = sep_2;
        sep3 = sep_3;
        return *this;
    }
    Printer set_sep(const std::string& sep_2) {
        sep2 = sep_2;
        return *this;
    }
    Printer set_end(const std::string& _end) {
        end = _end;
        return *this;
    }
};

}  // namespace bys
/**
 * @file scanner.hpp
 * @brief Input
 */
namespace bys {
class Scanner {
    std::istream& _is;
    template <class T, std::size_t... I>
    auto read_tuple(std::index_sequence<I...>) {
        return resolve_type_t<T>{read<typename std::tuple_element_t<I, T>>()...};
    }

   public:
    Scanner() = delete;
    Scanner(std::istream& is) : _is(is) { _is.tie(nullptr); }

    template <class T>
    auto read() {
        if constexpr (has_rshift_from_istream_v<T>) {
            T res;
            _is >> res;
            return res;
        } else if constexpr (is_tuple_like_v<T>) {
            return read_tuple<T>(std::make_index_sequence<std::tuple_size_v<T>>());
        } else if constexpr (is_indexed_v<T>) {
            typename T::resolve_to n;
            _is >> n;
            return --n;
        } else {
            static_assert([] { return false; }(), "TypeError");
        }
    }
    template <class... Ts, std::enable_if_t<(sizeof...(Ts) >= 2), std::nullptr_t> = nullptr>
    auto read() {
        return std::tuple{read<Ts>()...};
    }
    template <class T, std::size_t N>
    auto read() {
        std::array<resolve_type_t<T>, N> res;
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T>
    auto readvec(std::size_t n) {
        std::vector<resolve_type_t<T>> res(n);
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T>
    auto readvec(std::size_t n, std::size_t m) {
        std::vector<std::vector<resolve_type_t<T>>> res(n);
        for (auto&& e : res) e = readvec<T>(m);
        return res;
    }
};
}  // namespace bys
/**
 * @file io.hpp
 * @brief I/O
 */
namespace bys {
template <class... Args>
std::string debugfmt(int line, Args&&... args) {
    std::stringstream ss;
    Printer printer(ss);
    ss << "📌 line" << std::setw(4) << line << ": ";
    printer.set_sep("\n             ", " ", " ");
    printer.print(std::forward<Args>(args)...);
    return ss.str();
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
#define DEBUG(...) debug.cat(debugfmt(__LINE__, __VA_ARGS__)); debug.flush()
#else
#define DEBUG(...)
#endif
#define DEBUGCASE(casenum, ...) if (TESTCASE == casenum) DEBUG(__VA_ARGS__)
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
//! @brief [[maybe_unused]]な変数を生成。
#define UV [[maybe_unused]] auto CONCAT(unused_val_, __LINE__)
#define RE std::runtime_error("line: " + std::to_string(__LINE__) + ", func: " + __func__)
// clang-format on
#include <unistd.h>

/**
 * @file solver.hpp
 * @brief Solver
 */
namespace bys {
struct Solver {
    static inline int TESTCASE = 1;
    static void solve();
    static int main(int t = 1) {
        std::ios::sync_with_stdio(false);

        for (; TESTCASE <= t; ++TESTCASE) solve();
#ifdef LOCAL
        if (not std::cin.good()) std::cerr << "🟡 Input failed." << std::endl;
        if (not isatty(STDIN_FILENO) and not std::ws(std::cin).eof()) std::cerr << "🟡 Unused input." << std::endl;
#endif
        return 0;
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
struct Magma {
    using set_type = std::nullptr_t;
    static constexpr set_type operation(set_type, set_type);
    static constexpr set_type inverse(set_type);
    static constexpr set_type identity{nullptr};
    static constexpr bool commutative{false};
};
template <class T>
struct Add : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return a + b; }
    static constexpr set_type inverse(set_type a) { return -a; }
    static constexpr set_type identity{0};
    static constexpr bool commutative{true};
};
template <class T>
struct Min : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return std::min(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::max()};
};
template <class T>
struct Max : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return std::max(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::min()};
};
template <class T>
struct Update : Magma {
    using set_type = std::optional<T>;
    static constexpr set_type operation(set_type a, set_type b) { return b.has_value() ? b : a; }
    static constexpr set_type identity{std::nullopt};
};
template <class T>
struct Affine : Magma {
    using set_type = std::pair<T, T>;
    static constexpr set_type operation(set_type a, set_type b) { return {a.first * b.first, a.second * b.first + b.second}; }
    static constexpr set_type identity{1, 0};
};
template <class Modint>
struct ModMul : Magma {
    using set_type = Modint;
    static constexpr set_type operation(set_type a, set_type b) { return a * b; }
    static constexpr set_type inverse(set_type a) { return a.inv(); }
    static constexpr set_type identity{1};
    static constexpr bool commutative{true};
};
template <class T>
struct Xor : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return a ^ b; }
    static constexpr set_type inverse(set_type a) { return a; }
    static constexpr set_type identity{0};
    static constexpr bool commutative{true};
};
template <std::size_t N>
struct Perm : Magma {
    using set_type = std::array<int, N>;
    static constexpr set_type operation(const set_type& a, const set_type& b) {
        set_type res = {};
        for (auto i = 0UL; i < N; ++i) res[i] = b[a[i]];
        return res;
    }
    static constexpr set_type inverse(const set_type& a) {
        set_type res = {};
        for (auto i = 0UL; i < N; ++i) res[a[i]] = i;
        return res;
    }
    static constexpr set_type identity = []() {
        set_type res = {};
        for (auto i = 0UL; i < N; ++i) res[i] = i;
        return res;
    }();
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
/**
 * @file binary_indexed_tree.hpp
 * @brief Binary Indexed Tree
 */
namespace bys {
/**
 * @brief Binary Indexed Tree
 *
 * 一点更新: O(logN)
 * 区間和: O(logN)
 * See: https://algo-logic.info/binary-indexed-tree/
 */
template <class Abelian>
struct BinaryIndexedTree {
    using T = typename Abelian::set_type;
    static_assert(Abelian::commutative);
    const int _n;
    std::vector<T> data;

    BinaryIndexedTree(int n) : _n(n), data(_n + 1, Abelian::identity) {}
    BinaryIndexedTree(const std::vector<T>& val) : _n(val.size()), data(_n + 1, Abelian::identity) {
        std::copy(val.begin(), val.end(), data.begin() + 1);
        for (int i = 1; i <= _n; i++) {
            if (int j = i + (i & -i); j <= _n) data[j] = Abelian::operation(data[j], data[i]);
        }
    }

    void point_append(int i, T val) {
        assert(0 <= i && i < _n);
        for (++i; i <= _n; i += i & -i) data[i] = Abelian::operation(data[i], val);
    }

    void set(std::size_t i, T val) {
        assert(0 <= i and i < _n);
        point_append(i, Abelian::operation(Abelian::inverse(fold(i, i + 1)), val));
    }
    T operator[](std::size_t i) const { return fold(i, i + 1); }

    T prefix_fold(int right) const {
        assert(0 <= right and right <= _n);
        T res = Abelian::identity;
        for (; right > 0; right -= right & -right) res = Abelian::operation(res, data[right]);
        return res;
    }
    T fold(int left, int right) const {
        if (left < right) {
            return Abelian::operation(Abelian::inverse(prefix_fold(left)), prefix_fold(right));
        } else {
            return Abelian::identity;
        }
    }
};

template <class T>
struct BinaryIndexedTree<Add<T>> {
    const int _n;
    std::vector<T> data;

    BinaryIndexedTree(int n) : _n(n), data(_n + 1) {}
    BinaryIndexedTree(const std::vector<T>& val) : _n(val.size()), data(_n + 1) {
        std::copy(val.begin(), val.end(), data.begin() + 1);
        for (int i = 1; i <= _n; i++) {
            if (int j = i + (i & -i); j <= _n) data[j] += data[i];
        }
    }

    void point_append(int i, T val) {
        assert(0 <= i && i < _n);
        for (++i; i <= _n; i += i & -i) data[i] += val;
    }

    void set(std::size_t i, T val) {
        assert(0 <= i and i < _n);
        point_append(i, val - fold(i, i + 1));
    }
    T operator[](std::size_t i) const { return fold(i, i + 1); }

    T prefix_fold(int right) const {
        assert(0 <= right and right <= _n);
        T res = 0;
        for (; right > 0; right -= right & -right) res += data[right];
        return res;
    }
    T fold(int left, int right) const { return left < right ? prefix_fold(right) - prefix_fold(left) : 0; }

    //! @brief sum[0, r) >= xとなる最小のrを求める
    int bisect(T x) const {
        if (x <= 0) return 0;
        if (x > prefix_fold(_n)) return -1;
        int res = 0;
        for (int w = bit_floor(_n); w > 0; w >>= 1) {
            if (res + w < _n && data[res + w] < x) {
                x -= data[res + w];
                res += w;
            }
        }
        return res + 1;
    }
};

template <class T>
using FenwickTree = BinaryIndexedTree<Add<T>>;
template <class T>
BinaryIndexedTree<Add<T>> fenwick_tree(const std::vector<T>& val) {
    return BinaryIndexedTree<Add<T>>(val);
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
#include <cstddef>
namespace bys {
template <class Iterator>
class SubRange {
   public:
    using iterator = Iterator;
    using value_type = typename iterator::value_type;
    SubRange() = default;
    SubRange(const SubRange& s) : _begin(s._begin), _end(s._end) {}
    SubRange(const iterator& begin, const iterator& end) : _begin(begin), _end(end) {}

    iterator begin() const { return _begin; }
    iterator end() const { return _end; }
    auto operator[](std::size_t i) const { return *(_begin + i); }
    auto size() const { return _end - _begin; }
    bool empty() const { return _begin == _end; }

   private:
    iterator _begin, _end;
};
}  // namespace bys
namespace bys {
template <class T>
class IntegerIncrementIterator {
   public:
    using difference_type = T;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

    // constructors
    IntegerIncrementIterator() = default;
    explicit IntegerIncrementIterator(T x) : value(x) {}

    // essential operators for the range-based for statement
    IntegerIncrementIterator<T>& operator++() {
        ++value;
        return *this;
    }
    bool operator!=(const IntegerIncrementIterator& other) const { return value != other.value; }
    value_type operator*() const { return value; }

    // other operators
    IntegerIncrementIterator<T> operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }
    bool operator==(const IntegerIncrementIterator& other) const { return value == other.value; }

   private:
    value_type value;
};
template <class T>
class IntegerStepIterator {
   public:
    using difference_type = T;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

    // constructors
    IntegerStepIterator() = default;
    explicit IntegerStepIterator(T f, T x, T s) : start(f), value(x), step(s) {}

    // essential operators for the range-based for statement
    IntegerStepIterator<T>& operator++() {
        ++value;
        return *this;
    }
    bool operator!=(const IntegerStepIterator& other) const { return value != other.value; }
    value_type operator*() const { return start + value * step; }

    // other operators
    IntegerStepIterator<T> operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }
    bool operator==(const IntegerStepIterator& other) const { return value == other.value; }

   private:
    value_type start, value, step;
};

template <class T>
SubRange<IntegerIncrementIterator<T>> irange(T stop) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerIncrementIterator<T>;
    if (stop < static_cast<T>(0)) stop = static_cast<T>(0);
    return SubRange(iterator_t(static_cast<T>(0)), iterator_t(stop));
}
template <class T>
SubRange<IntegerIncrementIterator<T>> irange(T start, T stop) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerIncrementIterator<T>;
    if (stop < start) stop = start;
    return SubRange(iterator_t(start), iterator_t(stop));
}
template <class T>
SubRange<IntegerStepIterator<T>> irange(T start, T stop, T step) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerStepIterator<T>;
    assert(step != 0);
    auto w = step >= 0 ? stop - start : start - stop;
    auto s = step >= 0 ? step : -step;
    if (w < 0) w = 0;
    return SubRange(iterator_t(start, static_cast<T>(0), step), iterator_t(start, (w + s - 1) / s, step));
}
}  // namespace bys

namespace bys {
void Solver::solve() {
    auto n = scanner.read<int>();
    auto a = scanner.readvec<iint>(n);

    // set<int> seen;
    FenwickTree<int> bit(n);
    ll ans = 0;
    for (int i : irange(n)) {
        if (a[i] == i) {
            ans += bit.prefix_fold(a[i] + 1);
            bit.point_append(a[i], 1);
        }
        if (a[a[i]] < a[i] and a[a[i]] == i) ++ans;
    }

    print(ans);
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
