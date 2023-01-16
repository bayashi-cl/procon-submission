#include <array>
#include <limits>
#include <optional>
#include <utility>
#include <cstdint>
namespace bys {
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using i128 = __int128_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;

using isize = std::ptrdiff_t;
using usize = std::size_t;

#define DEFINE_NUM_LITERAL(name, type) \
    constexpr auto operator"" name(unsigned long long x) { return static_cast<type>(x); }

DEFINE_NUM_LITERAL(_i8, std::int8_t);
DEFINE_NUM_LITERAL(_i16, std::int16_t);
DEFINE_NUM_LITERAL(_i32, std::int32_t);
DEFINE_NUM_LITERAL(_i64, std::int64_t);
DEFINE_NUM_LITERAL(_i128, __int128_t);
DEFINE_NUM_LITERAL(_u8, std::uint8_t);
DEFINE_NUM_LITERAL(_u16, std::uint16_t);
DEFINE_NUM_LITERAL(_u32, std::uint32_t);
DEFINE_NUM_LITERAL(_u64, std::uint64_t);
DEFINE_NUM_LITERAL(_u128, __uint128_t);
DEFINE_NUM_LITERAL(_z, std::size_t);
#undef DEFINE_NUM_LITERAL
}  // namespace bys

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
template <class T> struct Add : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return a + b; }
    static constexpr set_type inverse(set_type a) { return -a; }
    static constexpr set_type identity{0};
    static constexpr bool commutative{true};
};
template <class T> struct Min : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return std::min(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::max()};
};
template <class T> struct Max : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return std::max(a, b); }
    static constexpr set_type identity{std::numeric_limits<set_type>::min()};
};
template <class T> struct Update : Magma {
    using set_type = std::optional<T>;
    static constexpr set_type operation(set_type a, set_type b) { return b.has_value() ? b : a; }
    static constexpr set_type identity{std::nullopt};
};
template <class T> struct Affine : Magma {
    using set_type = std::pair<T, T>;
    static constexpr set_type operation(set_type a, set_type b) { return {a.first * b.first, a.second * b.first + b.second}; }
    static constexpr set_type identity{1, 0};
};
template <class Modint> struct ModMul : Magma {
    using set_type = Modint;
    static constexpr set_type operation(set_type a, set_type b) { return a * b; }
    static constexpr set_type inverse(set_type a) { return a.inv(); }
    static constexpr set_type identity{1};
    static constexpr bool commutative{true};
};
template <class T> struct Xor : Magma {
    using set_type = T;
    static constexpr set_type operation(set_type a, set_type b) { return a ^ b; }
    static constexpr set_type inverse(set_type a) { return a; }
    static constexpr set_type identity{0};
    static constexpr bool commutative{true};
};
template <std::size_t N> struct Perm : Magma {
    using set_type = std::array<i32, N>;
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
#include <cassert>
#include <vector>

#include <algorithm>
#include <string>
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
template <class T> constexpr i32 bit_width(T x) {
    i32 bits = 0;
    x = (x < 0) ? (-x) : x;
    for (; x != 0; bits++) x >>= 1;
    return bits;
}
//! @brief 2冪に切り下げ
template <class T> constexpr T bit_floor(T x) {
    assert(x >= 0);
    return x == 0 ? 0 : T(1) << (bit_width(x) - 1);
}
//! @brief 2冪に切り上げ
template <class T> constexpr T bit_ceil(T x) {
    assert(x >= 0);
    return x == 0 ? 1 : T(1) << bit_width(x - 1);
}
//! @brief 2進文字列に変換
template <class T> std::string bin(T n) {
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
template <class T> constexpr bool pop(T s, i32 d) { return s & (T(1) << d); }
}  // namespace bys
/**
 * @file segment_tree.hpp
 * @brief Segment Tree
 */
namespace bys {
/**
 * @brief セグメント木
 *
 * 一点更新: O(logN)
 * 区間取得: O(logN)
 *
 * @tparam Monoid モノイド
 */
template <class Monoid> class SegmentTree {
    using value_type = typename Monoid::set_type;
    i32 _n, n_leaf;
    std::vector<value_type> data;

  public:
    SegmentTree(i32 n) : _n(n), n_leaf(bit_ceil(n)), data(n_leaf * 2, Monoid::identity) {}
    SegmentTree(i32 n, value_type init) : _n(n), n_leaf(bit_ceil(_n)), data(n_leaf * 2, Monoid::identity) {
        std::fill_n(data.begin() + n_leaf, n, init);
        for (i32 i = n_leaf - 1; i > 0; --i) data[i] = Monoid::operation(data[i * 2], data[i * 2 + 1]);
    }
    SegmentTree(const std::vector<value_type>& v) : _n(v.size()), n_leaf(bit_ceil(_n)), data(n_leaf * 2, Monoid::identity) {
        std::copy(v.begin(), v.end(), data.begin() + n_leaf);
        for (i32 i = n_leaf - 1; i > 0; --i) data[i] = Monoid::operation(data[i * 2], data[i * 2 + 1]);
    }

    value_type fold(i32 l, i32 r) const {
        assert(0 <= l && l <= _n);
        assert(l <= r);
        assert(r <= _n);

        value_type left = Monoid::identity, right = Monoid::identity;
        for (l += n_leaf, r += n_leaf; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = Monoid::operation(left, data[l++]);
            if (r & 1) right = Monoid::operation(data[--r], right);
        }
        return Monoid::operation(left, right);
    }

    value_type fold_all() const { return data[1]; }

    void update(i32 i, value_type val) {
        assert(0 <= i && i < _n);
        i += n_leaf;
        data[i] = val;
        for (i >>= 1; i > 0; i >>= 1) data[i] = Monoid::operation(data[i * 2], data[i * 2 + 1]);
    }

    value_type operator[](i32 i) const {
        assert(0 <= i && i < _n);
        return data[i + n_leaf];
    }

    // f(fold(l, r)) == true となる最大のr
    template <class Lambda, class... Args> i32 bisect_from_left(i32 l, Lambda f, Args... args) const {
        static_assert(std::is_same_v<std::invoke_result_t<Lambda, value_type, Args...>, bool>,
                      "The function signature is invalid.");
        assert(0 <= l && l < _n);
        assert(f(Monoid::identity, args...));
        l += n_leaf;
        value_type sm = Monoid::identity;
        do {
            l /= l & -l;
            if (!f(Monoid::operation(sm, data[l]), args...)) {
                while (l < n_leaf) {
                    l *= 2;
                    if (value_type op = Monoid::operation(sm, data[l]); f(op, args...)) {
                        sm = op;
                        ++l;
                    }
                }
                return l - n_leaf;
            }
            sm = Monoid::operation(sm, data[l]);
            ++l;
        } while ((l & -l) != l);
        return _n;
    }

    // f(fold(l, r)) == true となる最小のl
    template <class Lambda, class... Args> i32 bisect_from_right(i32 r, Lambda f, Args... args) const {
        static_assert(std::is_same_v<std::invoke_result_t<Lambda, value_type, Args...>, bool>,
                      "The function signature is invalid.");
        assert(0 <= r && r <= _n);
        assert(f(Monoid::identity, args...));
        if (r == 0) return 0;
        r += n_leaf;
        value_type sm = Monoid::identity;
        do {
            --r;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(Monoid::operation(data[r], sm))) {
                while (r < n_leaf) {
                    r = (2 * r + 1);
                    if (value_type op = Monoid::operation(data[r], sm); f(op, args...)) {
                        sm = op;
                        --r;
                    }
                }
                return r + 1 - n_leaf;
            }
            sm = op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
}  // namespace bys
/**
 * @file template.hpp
 * @author bayashi_cl
 *
 * C++ library for competitive programming by bayashi_cl
 * Repository: https://github.com/bayashi-cl/byslib
 * Document  : https://bayashi-cl.github.io/byslib/
 */
#ifndef LOCAL
#define NDEBUG
#endif

#include <cstddef>
#include <tuple>

#include <iostream>
#include <type_traits>
/**
 * @file traits.hpp
 * @brief Types
 *
 * type_traits拡張
 */
namespace bys {
template <class, class = void> struct has_rshift_from_istream : std::false_type {};
template <class T>
struct has_rshift_from_istream<T, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>())>> : std::true_type {};
template <class T> constexpr bool has_rshift_from_istream_v = has_rshift_from_istream<T>::value;

template <class, class = void> struct has_lshift_to_ostream : std::false_type {};
template <class T>
struct has_lshift_to_ostream<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T&>())>> : std::true_type {};
template <class T> constexpr bool has_lshft_to_ostream_v = has_lshift_to_ostream<T>::value;

template <class, class = void> struct is_tuple_like : std::false_type {};
template <class T> struct is_tuple_like<T, std::void_t<decltype(std::tuple_size<T>())>> : std::true_type {};
template <class T> constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

template <class, class = void> struct is_iterable : std::false_type {};
template <class T> struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>()))>> : std::true_type {};
template <class T> constexpr bool is_iterable_v = is_iterable<T>::value;

template <class T> struct Indexed {
    static_assert(std::is_integral_v<T>);
    using resolve_to = T;
};
using i32_1 = Indexed<i32>;
using i64_1 = Indexed<i64>;

template <class, class = void> struct is_indexed : std::false_type {};
template <class T> struct is_indexed<Indexed<T>> : std::true_type {};
template <class T> constexpr bool is_indexed_v = is_indexed<T>::value;

template <class T, class = void> struct resolve_type { using type = T; };
template <class T> struct resolve_type<T, std::void_t<typename T::resolve_to>> { using type = typename T::resolve_to; };
template <class T, std::size_t N> struct resolve_type<std::array<T, N>> {
    using type = std::array<typename resolve_type<T>::type, N>;
};
template <class T, class U> struct resolve_type<std::pair<T, U>> {
    using type = std::pair<typename resolve_type<T>::type, typename resolve_type<U>::type>;
};
template <class... Args> struct resolve_type<std::tuple<Args...>> {
    using type = std::tuple<typename resolve_type<Args>::type...>;
};
template <class T> using resolve_type_t = typename resolve_type<T>::type;
}  // namespace bys

/**
 * @file constant.hpp
 * @brief Const
 */
namespace bys {
constexpr i32 MOD7 = 1000000007;
constexpr i32 MOD9 = 998244353;
constexpr i32 MOD = MOD9;

template <class T> constexpr T get_inf();
namespace impl {
template <class Tp, std::size_t... I> constexpr auto get_inf_tuple(std::index_sequence<I...>) {
    return Tp{get_inf<typename std::tuple_element_t<I, Tp>>()...};
}
}  // namespace impl
template <class T> constexpr T get_inf() {
    if constexpr (std::is_integral_v<T>) {
        return std::numeric_limits<T>::max() / (T)2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::numeric_limits<T>::infinity();
    } else if constexpr (is_tuple_like_v<T>) {
        return impl::get_inf_tuple<T>(std::make_index_sequence<std::tuple_size_v<T>>());
    } else {
        static_assert([]() { return false; }, "Type Error");
    }
}
template <class T> constexpr bool is_inf(T x) { return x == get_inf<T>(); }
template <class T> constexpr auto inf_v = get_inf<T>();
constexpr auto INF = inf_v<i32>;
constexpr auto LINF = inf_v<i64>;
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
template <class T> constexpr bool chmax(T& a, T const& b) { return a < b ? a = b, true : false; }
/**
 * @brief 最小値で更新
 * @return true 更新されたとき
 */
template <class T> constexpr bool chmin(T& a, T const& b) { return a > b ? a = b, true : false; }
}  // namespace bys
#include <iterator>


namespace bys {
template <class Iterator> class SubRange {
  public:
    using iterator = Iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using value_type = typename iterator::value_type;
    using reference = value_type&;
    using const_reference = const value_type&;

    SubRange() = default;
    SubRange(const SubRange& s) : _begin(s._begin), _end(s._end) {}
    SubRange(const iterator& begin, const iterator& end) : _begin(begin), _end(end) {}

    iterator begin() const noexcept { return _begin; }
    iterator end() const noexcept { return _end; }
    reverse_iterator rbegin() const noexcept { return reverse_iterator{_end}; }
    reverse_iterator rend() const { return reverse_iterator{_begin}; }
    reference operator[](std::size_t i) noexcept { return *(_begin + i); }
    const_reference operator[](std::size_t i) const noexcept { return *(_begin + i); }
    auto size() const noexcept { return _end - _begin; }
    bool empty() const noexcept { return _begin == _end; }

    auto to_vec() const { return std::vector(_begin, _end); }

  private:
    iterator _begin, _end;
};
template <class Iterable> auto reversed(Iterable&& iter) {
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
template <class Iterator> struct EnumerateIterator {
  public:
    using difference_type = typename Iterator::difference_type;
    using value_type = std::tuple<i32, typename Iterator::value_type>;
    // using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::forward_iterator_tag;

    EnumerateIterator(const Iterator& iterator, i32 idx) : index(idx), value(iterator) {}

    auto& operator++() {
        ++value;
        ++index;
        return *this;
    }
    bool operator!=(const EnumerateIterator& other) const { return value != other.value; }
    auto operator*() const { return std::tie(index, *value); }

  private:
    i32 index;
    Iterator value;
};

/**
 * @brief enumerate
 *
 * @param iterable 対象
 * @param start indexの初期値
 */
template <class Iterable> auto enumerate(Iterable& iterable, i32 start = 0) {
    using iterator_t = EnumerateIterator<typename Iterable::iterator>;
    i32 end = static_cast<i32>(iterable.size()) + start;
    return SubRange(iterator_t(std::begin(iterable), start), iterator_t(std::end(iterable), end));
}
/**
 * @brief const enumerate
 *
 * @param iterable 対象
 * @param start indexの初期値
 */
template <class Iterable> auto cenumerate(Iterable& iterable, i32 start = 0) {
    using iterator_t = EnumerateIterator<typename Iterable::const_iterator>;
    i32 end = static_cast<i32>(iterable.size()) + start;
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
template <class T> class IntegerIncrementIterator {
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

template <class T> class IntegerStepIterator {
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

template <class T> SubRange<IntegerIncrementIterator<T>> irange(T stop) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerIncrementIterator<T>;
    if (stop < static_cast<T>(0)) stop = static_cast<T>(0);
    return SubRange(iterator_t(static_cast<T>(0)), iterator_t(stop));
}
template <class T> SubRange<IntegerIncrementIterator<T>> irange(T start, T stop) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerIncrementIterator<T>;
    if (stop < start) stop = start;
    return SubRange(iterator_t(start), iterator_t(stop));
}
template <class T> SubRange<IntegerStepIterator<T>> irange(T start, T stop, T step) {
    static_assert(std::is_integral_v<T>, "T is not integer.");
    using iterator_t = IntegerStepIterator<T>;
    assert(step != 0);
    auto w = step >= 0 ? stop - start : start - stop;
    auto s = step >= 0 ? step : -step;
    if (w < 0) w = 0;
    return SubRange(iterator_t(start, static_cast<T>(0), step), iterator_t(start, (w + s - 1) / s, step));
}
}  // namespace bys
using std::literals::string_literals::operator""s;
/**
 * @file macro.hpp
 * @brief Macro
 */
// clang-format off
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
//! @brief [[maybe_unused]]な変数を生成。
#define UV [[maybe_unused]] auto CONCAT(unused_val_, __LINE__)
#define RE std::runtime_error("file: "s + __FILE__ + ", line: "s + std::to_string(__LINE__) + ", func: "s + __func__)
#ifdef LOCAL
#define DEBUGBLOCK(block) block
#else
#define DEBUGBLOCK(block)
#endif
// clang-format on
#include <iomanip>

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

    template <std::size_t I, class T> void print_tuple_element(T&& elem) {
        if constexpr (I != 0) cat(sep3);
        cat(std::forward<T>(elem));
    }
    template <class Tp, std::size_t... I> void print_tuple(Tp&& tp, std::index_sequence<I...>) {
        (print_tuple_element<I>(std::forward<std::tuple_element_t<I, std::decay_t<Tp>>>(std::get<I>(tp))), ...);
    }

  public:
    Printer() = delete;
    Printer(std::ostream& os) : _os(os) { _os << std::fixed << std::setprecision(11) << std::boolalpha; }
    ~Printer() { _os << std::flush; }

    template <class T> void cat(T&& v) {
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
    template <class T> void print(T&& v) {
        cat(std::forward<T>(v));
        cat(end);
    }
    template <class T, class... Ts> void print(T&& top, Ts&&... args) {
        cat(std::forward<T>(top));
        cat(sep2);
        print(std::forward<Ts>(args)...);
    }
    template <class... Ts> void operator()(Ts&&... args) { print(std::forward<Ts>(args)...); }

    void flush() { _os << std::flush; }
    template <class... Ts> void send(Ts&&... args) {
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
    template <class T, std::size_t... I> auto read_tuple(std::index_sequence<I...>) {
        return resolve_type_t<T>{read<typename std::tuple_element_t<I, T>>()...};
    }

  public:
    Scanner() = delete;
    Scanner(std::istream& is) : _is(is) { _is.tie(nullptr); }

    template <class T> auto read() {
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
    template <class... Ts, std::enable_if_t<(sizeof...(Ts) >= 2), std::nullptr_t> = nullptr> auto read() {
        return std::tuple{read<Ts>()...};
    }
    template <class T, std::size_t N> auto read() {
        std::array<resolve_type_t<T>, N> res;
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T> auto readvec(i32 n) {
        std::vector<resolve_type_t<T>> res(n);
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T> auto readvec(i32 n, i32 m) {
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
template <class... Args> std::string debugfmt(i32 line, Args&&... args) {
    std::stringstream ss;
    Printer printer(ss);
    ss << "📌 line" << std::setw(4) << line << ": ";
    printer.set_sep("\n             ", " ", " ");
    printer.print(std::forward<Args>(args)...);
    return ss.str();
}

Printer print(std::cout), debug(std::cerr);
Scanner scanner(std::cin);

#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...)                                  \
    {                                               \
        debug.cat(debugfmt(__LINE__, __VA_ARGS__)); \
        debug.flush();                              \
    }
#else
#define DEBUG(...)
#endif
#define DEBUGCASE(casenum, ...) \
    if (TESTCASE == casenum) DEBUG(__VA_ARGS__)
//! @brief printしてreturnする。
#define EXIT(...)           \
    {                       \
        print(__VA_ARGS__); \
        return;             \
    }
}  // namespace bys

#include <unistd.h>



/**
 * @file solver.hpp
 * @brief Solver
 */
namespace bys {
struct Solver {
    static inline i32 TESTCASE = 1;
    static void solve();
    static i32 main(i32 t = 1) {
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
 * @file stdlib.hpp
 * @brief STL Template
 */
#include <bitset>
#include <cmath>
#include <complex>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>


namespace bys {
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs;

// alias
using Pa = std::pair<i32, i32>;
using Pa64 = std::pair<i64, i64>;
template <class T> using uset = std::unordered_set<T>;
template <class S, class T> using umap = std::unordered_map<S, T>;
}  // namespace bys

namespace bys {
template <class T> struct IsSorted : Magma {
    using set_type = std::tuple<bool, T, T>;
    static constexpr set_type operation(set_type a, set_type b) {
        auto [a_tf, a_min, a_max] = a;
        auto [b_tf, b_min, b_max] = b;
        bool sorted = a_tf & b_tf & (a_max <= b_min);
        return {sorted, std::min(a_min, b_min), std::max(a_max, b_max)};
    }
    static inline constexpr set_type identity = {true, get_inf<T>(), -get_inf<T>()};
    static constexpr set_type element(T v) { return {true, v, v}; }
};

template <std::size_t N> struct Add<std::array<i32, N>> {
    using set_type = std::array<i32, N>;
    static constexpr set_type operation(set_type a, set_type b) {
        set_type result = {};
        for (auto i = 0UL; i < N; ++i) result[i] = a[i] + b[i];
        return result;
    }
    static constexpr set_type identity = []() {
        set_type result = {};
        for (auto i = 0UL; i < N; ++i) result[i] = 0;
        return result;
    }();
    static constexpr set_type element(i32 v) {
        auto result = identity;
        result[v] = 1;
        return result;
    }
};

using AddCharSet = Add<std::array<i32, 26>>;
using IsSortedString = IsSorted<i32>;

void Solver::solve() {
    auto n = scanner.read<i32>();
    auto s = scanner.read<string>();
    auto q = scanner.read<i32>();

    vector<IsSortedString::set_type> s_sorted(n);
    vector<AddCharSet::set_type> s_charcnt(n);
    std::array<i32, 26> s_cnt;
    s_cnt.fill(0);
    for (auto i : irange(n)) {
        ++s_cnt[s[i] - 'a'];
        s_sorted[i] = IsSortedString::element(s[i]);
        s_charcnt[i] = AddCharSet::element((i32)(s[i] - 'a'));
    }
    SegmentTree<IsSortedString> seg_issorted(s_sorted);
    SegmentTree<AddCharSet> seg_charcnt(s_charcnt);

    for (UV : irange(q)) {
        auto t = scanner.read<i32>();
        if (t == 1) {
            auto [x, c] = scanner.read<i32_1, char>();
            --s_cnt[s[x] - 'a'];
            s[x] = c;
            ++s_cnt[s[x] - 'a'];
            seg_issorted.update(x, IsSortedString::element(c));
            seg_charcnt.update(x, AddCharSet::element((i32)(c - 'a')));
        } else {
            auto [l, r] = scanner.read<i32_1, i32>();
            auto [ans, mini, maxi] = seg_issorted.fold(l, r);
            if (ans) {
                auto t_cnt = seg_charcnt.fold(l, r);
                for (i32 i : irange(mini - 'a' + 1, maxi - 'a')) {
                    if (s_cnt[i] != t_cnt[i]) ans = false;
                }
            }
            print(ans ? "Yes" : "No");
        }
    }
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
