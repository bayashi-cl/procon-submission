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
/**
 * @file base.hpp
 * @brief Base
 */
//! @brief 幾何
namespace bys::geo {
constexpr ld EPS = 1e-9;
const ld PI = std::acos(-1.0);
const ld TAU = PI * 2;
int sgn(ld a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }
bool isclose(ld a, ld b) { return sgn(a - b) == 0; }
//! @brief 度数法 -> 弧度法
ld radian(ld degree) { return degree * (PI / 180.0); }
//! @brief 弧度法 -> 度数法
ld degree(ld theta) { return theta * (180.0 / PI); }
}  // namespace bys::geo
/**
 * @file point.hpp
 * @brief Point
 */
namespace bys::geo {
//! @brief 点/ベクトル
template <class T>
struct Point {
    T x, y;
    Point() : x(0.0), y(0.0) {}
    Point(T x, T y) : x(x), y(y) {}
    // clang-format off
    friend std::istream& operator>>(std::istream& is, Point& v) { return is >> v.x >> v.y; }
    friend std::ostream& operator<<(std::ostream& os, const Point& v) { return os << v.x << ' ' << v.y; }
    Point operator+() const { return *this; }
    Point operator-() const { return Point(-x, -y); }
    Point operator+(const Point& rh) const { return Point(x + rh.x, y + rh.y); }
    Point operator-(const Point& rh) const { return Point(x - rh.x, y - rh.y); }
    Point operator*(const T rh) const { return Point(x * rh, y * rh); }
    Point operator/(const T rh) const { return Point(x / rh, y / rh); }
    Point operator+=(const Point& rh) { x += rh.x; y += rh.y; return *this; }
    Point operator-=(const Point& rh) { x -= rh.x; y -= rh.y; return *this; }
    Point operator*=(const T rh) { x *= rh; y *= rh; return *this; }
    Point operator/=(const T rh) { x /= rh; y /= rh; return *this; }
    bool operator==(const Point& rh) const { return isclose(x, rh.x) && isclose(y, rh.y); }
    bool operator!=(const Point& rh) const { return !(*this == rh); }
    // clang-format on

    //! @brief ノルム^2
    T norm2() const { return x * x + y * y; }
    //! @brief ノルム
    ld norm() const { return std::sqrt(norm2()); }
    //! @brief 単位ベクトル
    Point normalized() const { return Point(x / norm(), y / norm()); }
    //! @brief 偏角
    ld angle() const { return std::atan2(y, x); }
    //! @brief 回転
    Point rotate(ld theta) const {
        ld ct = std::cos(theta), st = std::sin(theta);
        return Point(x * ct - y * st, x * st + y * ct);
    }
    Point rotate90() const { return Point(-y, x); }
    //! @brief マンハッタン距離用。45度回転して√2倍する
    Point manhattan_rotate() const { return Point(x - y, x + y); }
    //! @brief 内積
    T dot(const Point& rh) const { return x * rh.x + y * rh.y; }
    //! @brief 外積
    T det(const Point& rh) const { return x * rh.y - y * rh.x; }
    //! @brief 法線ベクトル
    Point normal() const { return Point(-normalized().y, normalized().x); }
    //! @brief 正射影ベクトル
    Point projection(const Point& to) const { return to * (dot(to) / to.norm2()); }
    //! @brief 象限
    int quadrant() const {
        if (sgn(y) >= 0) return sgn(x) >= 0 ? 1 : 2;
        return sgn(x) >= 0 ? 4 : 3;
    }
    //! @brief 偏角ソート用
    bool operator<(const Point& rh) const {
        int q = quadrant(), rhq = rh.quadrant();
        if (q != rhq) return q < rhq;
        return sgn(det(rh)) > 0;
    }
    bool operator<=(const Point& rh) const {
        int q = quadrant(), rhq = rh.quadrant();
        if (q != rhq) return q < rhq;
        return sgn(det(rh)) >= 0;
    }
};

template <class T>
bool compx(Point<T>& a, Point<T>& b) {
    return a.x < b.x;
}
template <class T>
bool compy(Point<T>& a, Point<T>& b) {
    return a.y < b.y;
}
//! @brief 曲がる方向
enum class Turn {
    //! abの後方
    Back = -2,
    //! ab->bcが右に曲がる
    CW = -1,
    //! ab上
    Middle = 0,
    //! ab->bcが左に曲がる
    CCW = 1,
    //! abの前方
    Front = 2,
};
//! @brief 辺の曲がる方向
template <class T>
Turn iSP(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    int flg = sgn((b - a).det(c - a));
    if (flg == 1) {
        return Turn::CCW;
    } else if (flg == -1) {
        return Turn::CW;
    } else {
        if (sgn((b - a).dot(c - b)) > 0) {
            return Turn::Front;
        } else if (sgn((a - b).dot(c - a)) > 0) {
            return Turn::Back;
        } else {
            return Turn::Middle;
        }
    }
}
enum class Angle {
    //! 鈍角
    Obtuse = -1,
    //! 直角
    Right = 0,
    //! 鋭角
    Acute = 1,
};

//! @brief 角の種類
template <class T>
Angle angle_type(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    int t = sgn((a - b).dot(c - b));
    if (t == -1) {
        return Angle::Obtuse;
    } else if (t == 0) {
        return Angle::Right;
    } else {
        return Angle::Acute;
    }
}
template <class T>
T distance2(const Point<T>& a, const Point<T>& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
template <class T>
T distance(const Point<T>& a, const Point<T>& b) {
    return sqrt(distance2(a, b));
}
}  // namespace bys::geo
/**
 * @file grid.hpp
 * @brief Grid Manager
 */
namespace bys {
//! @brief グリッド探索補助ツール詰め合わせ
struct Grid {
    int h, w;
    //! @brief row*colのグリッド
    Grid(int row, int col) : h(row), w(col) {}

    //! @brief グリッドに含まれるか判定
    bool contain(int row, int col) const { return 0 <= row && row < h && 0 <= col && col < w; }
    //! @brief グリッドの面積
    int area() const { return h * w; }
    //! @brief 一次元化したときのインデックス
    int index(int row, int col) const {
        assert(contain(row, col));
        return row * w + col;
    }
    int index(std::pair<int, int> p) const { return index(p.first, p.second); }
    //! @brief インデックスから復元
    std::pair<int, int> coord(int idx) const {
        assert(0 <= idx && idx < area());
        return {idx / w, idx % w};
    }
    //! 周囲のマスのうちグリッドに含まれるもの
    auto next(int row, int col, const vector<pair<int, int>>& delta) const {
        assert(contain(row, col));
        std::vector<std::pair<int, int>> res;
        for (auto [di, dj] : delta) {
            int ni = row + di;
            int nj = col + dj;
            if (contain(ni, nj)) res.push_back({ni, nj});
        }
        return res;
    }
    //! @brief 右・下
    auto next2(int row, int col) const { return next(row, col, {{1, 0}, {0, 1}}); }
    //! @brief 上下左右
    auto next4(int row, int col) const { return next(row, col, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}); }
    //! @brief 8方向
    auto next8(int row, int col) const {
        vector<pair<int, int>> delta;
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                delta.push_back({di, dj});
            }
        }
        return next(row, col, delta);
    }
};
}  // namespace bys

namespace bys {
void Solver::solve() {
    using P = geo::Point<int>;

    auto s = scanner.readvec<string>(9);
    Grid g(9, 9);
    vector<P> pawn;

    for (int i : irange(9)) {
        for (int j : irange(9)) {
            if (s[i][j] == '#') pawn.push_back({i, j});
        }
    }
    int ans = 0;
    for (auto&& a : pawn) {
        for (auto&& b : pawn) {
            if (a == b) continue;
            auto rot = (b - a).rotate90();
            auto p = b + rot;
            auto q = a + rot;
            if (g.contain(p.x, p.y) and g.contain(q.x, q.y)) {
                if (s[p.x][p.y] == '#' and s[q.x][q.y] == '#') {
                    ++ans;
                }
            }
        }
    }
    print(ans / 4);
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
