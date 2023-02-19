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
#include <limits>
#include <tuple>
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
#include <array>
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
#include <vector>


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
#include <string>
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
#include <algorithm>
#include <bitset>
#include <cassert>
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
void Solver::solve() {
    auto [n, d, k] = scanner.read<i64, 3>();
    // --k;
    d %= n;
    auto g = std::gcd(n, d);
    if (d == 0) {
        print(k - 1);
    } else if (g == 1) {
        print(d * (k - 1) % n);
    } else {
        auto ans = (d * (k - 1)) % n + (k - 1) / (n / g);
        DEBUGBLOCK({
            vector<bool> b(n);
            i32 now = 0;
            i32 cnt = 0;
            while (true) {
                // DEBUG(now);
                b[now] = true;
                cnt++;
                if (cnt == k) break;
                now = (now + d) % n;
                while (b[now]) now = (now + 1) % n;
            }
            if (ans != now) {
                DEBUG("fail!");
                DEBUG(n, d, k);
                DEBUG(ans, now);
            }
        })
        print(ans);
    }
}
}  // namespace bys

int main() { return bys::Solver::main(bys::scanner.read<bys::i32>()); }
