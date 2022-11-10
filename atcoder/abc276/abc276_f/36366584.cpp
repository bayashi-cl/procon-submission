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
using int1 = Indexed<int>;
using ll1 = Indexed<long long int>;

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
 * @file const.hpp
 * @brief Const
 */
namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;

template <class T>
constexpr T get_inf();
namespace impl {
template <class Tp, std::size_t... I>
constexpr auto get_inf_tuple(std::index_sequence<I...>) {
    return Tp{get_inf<typename std::tuple_element_t<I, Tp>>()...};
}
}  // namespace impl
template <class T>
constexpr T get_inf() {
    if constexpr (std::is_integral_v<T>) {
        return std::numeric_limits<T>::max() / 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::numeric_limits<T>::infinity();
    } else if constexpr (is_tuple_like_v<T>) {
        return impl::get_inf_tuple<T>(std::make_index_sequence<std::tuple_size_v<T>>());
    } else {
        static_assert([]() { return false; }, "Type Error");
    }
}
constexpr int INF = get_inf<int>();
constexpr ll LINF = get_inf<ll>();
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
    Printer(std::ostream& os) : _os(os) { _os << std::fixed << std::setprecision(11) << std::boolalpha; }
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
            bool top = true;
            for (auto&& vi : v) {
                top ? (void)(top = false) : cat(sep);
                cat(vi);
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
#include <tuple>

#include <cstddef>


namespace bys {
template <class Iterator>
class SubRange {
   public:
    using iterator = Iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using value_type = typename iterator::value_type;

    SubRange() = default;
    SubRange(const SubRange& s) : _begin(s._begin), _end(s._end) {}
    SubRange(const iterator& begin, const iterator& end) : _begin(begin), _end(end) {}

    iterator begin() const noexcept { return _begin; }
    iterator end() const noexcept { return _end; }
    reverse_iterator rbegin() const noexcept { return reverse_iterator{_end}; }
    reverse_iterator rend() const { return reverse_iterator{_begin}; }
    auto operator[](std::size_t i) const noexcept { return *(_begin + i); }
    auto size() const noexcept { return _end - _begin; }
    bool empty() const noexcept { return _begin == _end; }

    auto to_vec() const { return std::vector(_begin, _end); }

   private:
    iterator _begin, _end;
};
template <class Iterable>
auto reversed(Iterable&& iter) {
    static_assert(is_iterable_v<Iterable>, "iter is not iterable");
    return SubRange(std::rbegin(std::forward<Iterable>(iter)), std::rend(std::forward<Iterable>(iter)));
}
}  // namespace bys
/**
 * @file enumerate.hpp
 * @brief Python::enumerate
 *
 * Python再現シリーズ enumerate編
 * See: https://docs.python.org/ja/3/library/functions.html#enumerate
 */
namespace bys {
template <class Iterator>
struct EnumerateIterator {
   public:
    using difference_type = typename Iterator::difference_type;
    using value_type = std::tuple<int, typename Iterator::value_type>;
    // using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;

    EnumerateIterator(const Iterator& iterator, int idx) : index(idx), value(iterator) {}

    auto& operator++() {
        ++value;
        ++index;
        return *this;
    }
    bool operator!=(const EnumerateIterator& other) const { return value != other.value; }
    auto operator*() const { return std::tie(index, *value); }

   private:
    int index;
    Iterator value;
};

/**
 * @brief enumerate
 *
 * @param iterable 対象
 * @param start indexの初期値
 */
template <class Iterable>
auto enumerate(Iterable& iterable, int start = 0) {
    using iterator_t = EnumerateIterator<typename Iterable::iterator>;
    int end = static_cast<int>(iterable.size()) + start;
    return SubRange(iterator_t(std::begin(iterable), start), iterator_t(std::end(iterable), end));
}
/**
 * @brief const enumerate
 *
 * @param iterable 対象
 * @param start indexの初期値
 */
template <class Iterable>
auto cenumerate(Iterable& iterable, int start = 0) {
    using iterator_t = EnumerateIterator<typename Iterable::const_iterator>;
    int end = static_cast<int>(iterable.size()) + start;
    return SubRange(iterator_t(std::cbegin(iterable), start), iterator_t(std::cend(iterable), end));
}
}  // namespace bys
/**
 * @file irange.hpp
 * @brief Python::range
 *
 * Python再現シリーズ range編
 * See: https://docs.python.org/ja/3/library/stdtypes.html#range
 */
namespace bys {
template <class T>
class IntegerIncrementIterator {
   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit IntegerIncrementIterator(T x) : value(x) {}

    reference operator*() noexcept { return value; }
    const reference operator*() const noexcept { return value; }

    auto operator++() noexcept {
        ++value;
        return *this;
    }
    auto operator++(int) noexcept {
        auto temp = *this;
        ++*this;
        return temp;
    }
    auto operator--() noexcept {
        --value;
        return *this;
    }
    auto operator--(int) {
        auto temp = *this;
        --*this;
        return temp;
    }

    bool operator!=(IntegerIncrementIterator const& other) const { return value != other.value; }
    bool operator==(IntegerIncrementIterator const& other) const { return value == other.value; }

   private:
    value_type value;
};

template <class T>
class IntegerStepIterator {
   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit IntegerStepIterator(T f, T x, T s) : start(f), value(x), step(s) {}

    reference operator*() noexcept { return start + value * step; }
    const reference operator*() const noexcept { return start + value * step; }

    auto operator++() {
        ++value;
        return *this;
    }
    auto operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }
    auto operator--() {
        --value;
        return *this;
    }
    auto operator--(int) {
        auto temp = *this;
        --*this;
        return temp;
    }

    bool operator!=(IntegerStepIterator const& other) const { return value != other.value; }
    bool operator==(IntegerStepIterator const& other) const { return value == other.value; }

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
namespace impl {
template <typename T, std::size_t N>
struct NdVector {
    using type = std::vector<typename NdVector<T, N - 1>::type>;
};
template <typename T>
struct NdVector<T, 1> {
    using type = std::vector<T>;
};

template <typename T, std::size_t N>
auto ndvector(std::vector<size_t>& shape, T const& fill_value) {
    if constexpr (N == 1) {
        return std::vector(shape[0], fill_value);
    } else {
        std::size_t size = shape.back();
        shape.pop_back();
        return std::vector(size, ndvector<T, N - 1>(shape, fill_value));
    }
}
}  // namespace impl

template <class T, std::size_t N>
using NdVector = typename impl::NdVector<T, N>::type;

/**
 * @brief n-dimentional vector
 *
 * @example auto v = ndvector({2, 3}, 4); // {{4, 4, 4}, {4, 4, 4}}
 */
template <class T, std::size_t N>
auto ndvector(const std::size_t (&shape)[N], const T& fill_value = T()) {
    static_assert(N > 0);
    std::vector shape_vec(std::crbegin(shape), std::crend(shape));
    return impl::ndvector<T, N>(shape_vec, fill_value);
}
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
    assert(n >= 0);
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
#include <cstdint>
namespace bys {
// numpy style number types
using i1 = std::int8_t;
using i2 = std::int16_t;
using i4 = std::int32_t;
using i8 = std::int64_t;
using i16 = __int128_t;
using u1 = std::uint8_t;
using u2 = std::uint16_t;
using u4 = std::uint32_t;
using u8 = std::uint64_t;
using u16 = __uint128_t;
using f4 = float;
using f8 = double;
using f16 = long double;
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
    // T res = 1 % mod;
    if (mod == 1) return 0;
    T res = 1;
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

//! @brief Count multipules of k in the [left, right)
template <class T>
constexpr T range_multiples(T left, T right, T k) {
    return (right - 1) / k - (left - 1) / k;
}
template <class T>
constexpr T multiple_floor(T x, T k) {
    return x / k * k;
}
template <class T>
constexpr T multiple_ceil(T x, T k) {
    return ceildiv(x, k) * k;
}
}  // namespace bys
/**
 * @file prime.hpp
 * @brief Prime
 */
namespace bys {
/**
 * @brief 素因数分解
 *
 * 試し割り法
 * O(√n)
 */
template <typename T>
std::vector<T> prime_factorize(T n) {
    vector<T> res;
    while (n % 2 == 0) {
        res.push_back(2);
        n /= 2;
    }
    T f = 3;
    while (f * f <= n) {
        if (n % f == 0) {
            res.push_back(f);
            n /= f;
        } else {
            f += 2;
        }
    }
    if (n != 1) res.push_back(n);
    return res;
}

/**
 * @brief Miller-Rabin素数判定
 *
 * 2^64以下なら正確に判定できる
 * See: https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 * See: https://miller-rabin.appspot.com
 */
constexpr bool is_prime(i16 n) {
    if (not(n & 1)) return n == 2;
    if (n <= 1) return false;
    auto d = n - 1;
    while (d % 2 == 0) d >>= 1;
    std::array<i16, 9> base = {2, 7, 61, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (auto b : base) {
        if (n <= b) break;
        auto t = d;
        auto y = mod_pow(b, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
}  // namespace bys
/**
 * @file modint.hpp
 * @brief Modint
 */
namespace bys {
/**
 * @brief ModInt
 *
 * ac-libraryのmodintをconstexpr化したもの
 * See: https://atcoder.github.io/ac-library/document_ja/modint.html
 *
 * @tparam Modulo 法
 */
template <unsigned int Modulo>
class ModInt {
    unsigned int _v;

   public:
    static constexpr unsigned int mod = Modulo;
    // static_assert(is_prime(mod), "Modulo need to be prime.");
    static_assert(mod < (std::numeric_limits<unsigned int>::max() >> 1), "Modulo need to be <2^31.");

    constexpr ModInt() noexcept : _v(0) {}
    template <class T, std::enable_if_t<std::is_unsigned_v<T>, std::nullptr_t> = nullptr>
    constexpr ModInt(T v) noexcept : _v(v % mod) {}
    template <class T, std::enable_if_t<std::is_signed_v<T>, std::nullptr_t> = nullptr>
    constexpr ModInt(T v) noexcept : _v(floormod(v, mod)) {}

    constexpr ModInt pow(ll n) const noexcept {
        ModInt res = 1, p = *this;
        while (n) {
            if (n & 1) res *= p;
            p *= p;
            n >>= 1;
        }
        return res;
    }
    constexpr ModInt inv() const noexcept {
        if constexpr (is_prime(mod)) {
            return pow(mod - 2);
        } else {
            return inv_gcd(_v, mod).second;
        }
    }

    constexpr ModInt& operator+=(const ModInt rhs) noexcept {
        _v += rhs._v;
        if (_v >= mod) _v -= mod;
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt rhs) noexcept {
        if (rhs._v > _v) _v += mod;
        _v -= rhs._v;
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt rhs) noexcept {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % mod);
        return *this;
    }
    constexpr ModInt& operator/=(const ModInt rhs) noexcept { return *this = *this * rhs.inv(); }

    constexpr ModInt operator+() const noexcept { return *this; }
    constexpr ModInt operator-() const noexcept { return ModInt() - *this; }
    constexpr ModInt& operator++() noexcept {
        _v++;
        if (_v == mod) _v = 0;
        return *this;
    }
    constexpr ModInt& operator--() noexcept {
        if (_v == 0) _v = mod;
        --_v;
        return *this;
    }
    constexpr ModInt operator++(int) noexcept {
        ModInt res = *this;
        ++*this;
        return res;
    }
    constexpr ModInt operator--(int) noexcept {
        ModInt res = *this;
        --*this;
        return res;
    }

    friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) noexcept { return ModInt(lhs) += rhs; }
    friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) noexcept { return ModInt(lhs) -= rhs; }
    friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) noexcept { return ModInt(lhs) *= rhs; }
    friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) noexcept { return ModInt(lhs) /= rhs; }
    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) noexcept { return lhs._v == rhs._v; }
    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) noexcept { return lhs._v != rhs._v; }

    friend std::istream& operator>>(std::istream& is, ModInt& m) noexcept { return is >> m._v; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& m) noexcept { return os << m._v; }
};
using Mint = ModInt<998244353>;
using Mint7 = ModInt<1000000007>;
}  // namespace bys
namespace bys {
void Solver::solve() {
    auto n = scanner.read<int>();
    auto a = scanner.readvec<ll>(n);
    auto maxi_a = *std::max_element(a.begin(), a.end()) + 1;

    FenwickTree<ll> fen_small(maxi_a), fen_large(maxi_a);
    Mint ans = 0;
    for (ll k : irange(1, n + 1)) {
        auto ak = a[k - 1];

        ans += Mint(ak) * fen_small.fold(0, ak) * 2;
        ans += fen_large.fold(ak, maxi_a) * 2;

        fen_small.point_append(ak, 1);
        fen_large.point_append(ak, ak);

        ans += ak;
        print(ans / (k * k));
    }
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
