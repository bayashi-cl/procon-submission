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
template <class T>
constexpr bool is_inf(T x) {
    return x == get_inf<T>();
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
 * @file fixpoint.hpp
 * @brief FixPoint
 */
namespace bys {
/**
 * @brief ラムダ再帰
 *
 * @see: https://koturn.hatenablog.com/entry/2018/06/10/060000
 */
template <typename F>
struct FixPoint : F {
    FixPoint(F &&f) : F{std::forward<F>(f)} {}
    template <typename... Args>
    decltype(auto) operator()(Args &&...args) const {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};

/**
 * @brief メモ化再帰
 *
 * @see ?
 */
template <class F>
class Cache : F {
    template <class>
    struct get_signature {};

    template <class Fn, class R, class Self, class... Args>
    struct get_signature<R (Fn::*)(Self, Args...) const> {
        using result_type = R;
        using args_tuple = std::tuple<std::decay_t<Args>...>;
    };

    using signature = get_signature<decltype(&F::template operator()<Cache<F> &>)>;
    using args_tuple = typename signature::args_tuple;
    using result_type = typename signature::result_type;

    std::map<args_tuple, result_type> memo;

   public:
    Cache(F &&fn) : F{std::forward<F>(fn)} {}

    template <class... Args>
    result_type operator()(Args &&...args) {
        args_tuple key{std::forward<Args>(args)...};
        if (auto itr = memo.find(key); itr == memo.end()) {
            result_type res = F::operator()(*this, std::forward<Args>(args)...);
            memo.emplace(key, res);
            return res;
        } else {
            return itr->second;
        }
    }
};
}  // namespace bys


#include <utility>


namespace bys {
template <class T>
struct CSRMatrix;
}

namespace bys {
template <class T>
class COOMatrix {
   public:
    using value_type = T;
    const std::pair<int, int> shape;

   private:
    std::vector<std::tuple<int, int, T>> _data;
    std::vector<int> _col_cnt;

   public:
    COOMatrix(int n, int m = -1) : shape{n, m}, _col_cnt(n) {}

    void set(int i, int j, const T& v) {
        assert(0 <= i and i < shape.first);
        ++_col_cnt[i];
        _data.emplace_back(i, j, v);
    }
    void push_back(int i, T&& v) { set(i, _col_cnt[i], std::forward<T>(v)); }
    template <class... Args>
    void emplace_back(int i, Args&&... args) {
        set(i, _col_cnt[i], {std::forward<Args>(args)...});
    }
    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

    void sort() {
        std::sort(_data.begin(), _data.end(), [](const std::tuple<int, int, T>& a, const std::tuple<int, int, T>& b) {
            return std::get<2>(a) < std::get<2>(b);
        });
    }
    std::size_t size() const { return shape.first; }
    std::size_t nonzero() const { return _data.size(); }

    friend CSRMatrix<T>;
};
}  // namespace bys

namespace bys {
template <class T>
class CSRMatrix {
   public:
    using value_type = T;
    const std::pair<int, int> shape;

   private:
    std::vector<int> _indptr, _indices;
    std::vector<T> _data;

   public:
    CSRMatrix(const COOMatrix<T>& coo)
        : shape(coo.shape), _indptr(coo._col_cnt), _indices(coo._data.size()), _data(coo._data.size()) {
        _indptr.push_back(0);

        std::partial_sum(_indptr.begin(), _indptr.end(), _indptr.begin());
        for (auto&& [i, j, v] : coo._data) {
            int index = --_indptr[i];
            _indices[index] = j;
            _data[index] = v;
        }
    }
    CSRMatrix(std::pair<int, int> shape, const std::vector<std::vector<std::pair<int, T>>>& data)
        : shape(shape), _indptr(shape.first + 1) {
        for (int i = 0; i < shape.first; ++i) {
            for (auto&& [index, elem] : data[i]) {
                _indices.push_back(index);
                _data.push_back(elem);
            }
            _indptr[i + 1] += _indptr[i] + data[i].size();
        }
    }
    auto operator[](std::size_t i) const { return SubRange(_data.cbegin() + _indptr[i], _data.cbegin() + _indptr[i + 1]); }
    std::size_t size() const { return shape.first; }
};
}  // namespace bys

namespace bys {
struct EdgeBase {};

template <class WeightType = std::int64_t, class VertexType = std::size_t>
struct Edge : EdgeBase {
    using weight_type = WeightType;
    using vertex_type = VertexType;
    vertex_type src, dest;
    weight_type weight;

    Edge() : src(-1), dest(-1), weight(get_inf<weight_type>()) {}
    Edge(vertex_type src_, vertex_type dest_, weight_type weight_ = 1) : src(src_), dest(dest_), weight(weight_) {}

    bool operator<(const Edge& other) const { return weight < other.weight; }
    friend std::ostream& operator<<(std::ostream& os, Edge const& e) {
        return os << '{' << e.src << " -> " << e.dest << ": " << e.weight << '}';
    }
};

template <class InfoType, class WeightType = std::int64_t, class VertexType = std::size_t>
struct InfoEdge : Edge<WeightType, VertexType> {
    using info_type = InfoType;
    using super = Edge<WeightType, VertexType>;
    using super::Edge;
    using typename super::vertex_type;
    using typename super::weight_type;

    info_type info;
    InfoEdge(vertex_type src_, vertex_type dest_, weight_type weight_ = 1, info_type info_ = info_type())
        : super(src_, dest_, weight_), info(info_) {}
};

template <class E>
constexpr bool is_edge_v = std::is_base_of_v<EdgeBase, E>;
}  // namespace bys

namespace bys {
template <class E>
struct EdgeList : public COOMatrix<E> {
    using edge_type = E;
    using vertex_type = typename edge_type::vertex_type;
    using weight_type = typename edge_type::weight_type;
    using super = COOMatrix<E>;
    using super::COOMatrix;

    void add_edge(edge_type& edge) { super::push_back(edge.src, std::forward<edge_type>(edge)); }
    void add_edge(vertex_type src, vertex_type dest, weight_type weight = 1) { super::push_back(src, {src, dest, weight}); }
    void add_undirected_edge(vertex_type u, vertex_type v, weight_type weight = 1) {
        super::push_back(u, {u, v, weight});
        super::push_back(v, {v, u, weight});
    }
    auto adj() const { return CSRMatrix<edge_type>(*this); }
};
using EList = EdgeList<Edge<>>;

template <class E>
using AdjacencyList = CSRMatrix<E>;
using AdjList = AdjacencyList<Edge<>>;
}  // namespace bys

namespace bys {
template <class E>
auto dfs(AdjacencyList<E> const& graph, typename E::vertex_type source) {
    using V = typename E::vertex_type;
    std::vector<bool> seen(graph.size());
    std::vector<V> res;
    std::stack<V> st;
    st.push(source);
    while (not st.empty()) {
        auto top = st.top();
        st.pop();
        seen[top] = true;
        res.push_back(top);
        for (auto&& e : graph[top]) {
            if (not seen[e.dest]) {
                st.push(e.dest);
            }
        }
    }
}
template <class E>
auto pre_order(const AdjacencyList<E>& graph) {
    using V = typename E::vertex_type;
    int n = graph.size();
    std::vector<bool> seen(n);
    std::vector<V> res;
    FixPoint pre_dfs([&](auto&& self, V now) -> void {
        seen[now] = true;
        res.push_back(now);
        for (auto&& e : graph[now]) {
            if (not seen[e.dest]) self(e.dest);
        }
    });
    for (int i = 0; i < n; ++i) {
        if (not seen[i]) pre_dfs(i);
    }
    return res;
}

// std::vector<int> in_order(const AdjacencyList& graph, int source);
template <class E>
auto post_order(const AdjacencyList<E>& graph) {
    using V = typename E::vertex_type;
    int n = graph.size();
    std::vector<bool> seen(n);
    std::vector<V> res;
    FixPoint post_dfs([&](auto&& self, V now) -> void {
        seen[now] = true;
        for (auto&& e : graph[now]) {
            if (not seen[e.dest]) self(e.dest);
        }
        res.push_back(now);
    });
    for (int i = 0; i < n; ++i) {
        if (not seen[i]) post_dfs(i);
    }
    return res;
}
// std::vector<int> euler_tour(const AdjacencyList& graph, int source);
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
    auto n = scanner.read<int>();
    auto s = scanner.readvec<string>(n);

    Grid g(26, 1 << n);
    EdgeList<Edge<int>> elist(g.area());
    for (int i : irange(n)) {
        int f = s[i].front() - 'a';
        int t = s[i].back() - 'a';

        for (int a : irange(1 << n)) {
            if (pop(a, i)) continue;
            elist.add_edge(g.index(f, a), g.index(t, a | (1 << i)));
        }
    }
    auto graph = elist.adj();

    vector<bool> dp(graph.size());
    for (auto now : post_order(graph)) {
        auto [c, a] = g.coord(now);
        if (__builtin_popcount(a) % 2 == 0) {  // first
            dp[now] = false;
            for (auto&& nxt : graph[now]) {
                if (dp[nxt.dest]) dp[now] = true;
            }
        } else {  // second
            dp[now] = true;
            for (auto&& nxt : graph[now]) {
                if (not dp[nxt.dest]) dp[now] = false;
            }
        }
    }

    auto ans = false;
    for (int i : irange(26)) {
        if (dp[g.index(i, 0)]) ans = true;
    }
    print(ans ? "First" : "Second");
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
