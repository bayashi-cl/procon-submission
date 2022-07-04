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
    Printer(std::ostream& os_) : os(os_) { os << std::fixed << std::setprecision(11) << std::boolalpha; }
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
    Scanner(std::istream& is_) : is(is_) { is.tie(nullptr); }

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
template <class... Args>
std::string debugfmt(int line, Args&&... args) {
    std::stringstream ss;
    Printer printer(ss);
    ss << "📌 line" << std::setw(4) << line << ": ";
    std::string space = "\n             ";
    printer.set(" ", space).print(std::forward<Args>(args)...);
    auto result = ss.str();
    return result.substr(0, result.length() - space.length());
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
#define DEBUG(...) debug(debugfmt(__LINE__, __VA_ARGS__));
#else
#define DEBUG(...)
#endif
#define DEBUGCASE(casenum, ...) if (TESTCASE == casenum) DEBUG(__VA_ARGS__);
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
    static inline int TESTCASE = 1;
    static void solve();
    static int main(int t = 1) {
        std::ios::sync_with_stdio(false);

        for (; TESTCASE <= t; ++TESTCASE) solve();

        if (not std::cin.good()) std::cerr << "🟡 Input failed." << std::endl;
        if (not std::ws(std::cin).eof()) std::cerr << "🟡 Unused input." << std::endl;
        return 0;
    }
};
}  // namespace bys
// -------------------------------------
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
    void push_back(int i, const T& v) { set(i, _col_cnt[i], v); }
    template <class... Args>
    void emplace_back(int i, Args... args) {
        set(i, _col_cnt[i], {args...});
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
template <class Itr>
struct ItrRange {
    Itr _begin, _end;
    ItrRange(Itr begin, Itr end) : _begin(begin), _end(end){};
    Itr begin() const { return _begin; }
    Itr end() const { return _end; }
    auto operator[](std::size_t i) const { return *(_begin + i); }
    std::size_t size() const { return std::distance(_begin, _end); }
    bool empty() const { return size() == 0; }
};

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
    auto operator[](std::size_t i) const { return ItrRange(_data.cbegin() + _indptr[i], _data.cbegin() + _indptr[i + 1]); }
    std::size_t size() const { return shape.first; }
};
}  // namespace bys

namespace bys {
struct Edge {
    int dest;
    ll weight;
    Edge() = default;
    Edge(int dest, ll weight = 1) : dest(dest), weight(weight) {}
    bool operator<(const Edge& other) const { return weight < other.weight; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        return os << "{ -> " << e.dest << ": " << e.weight << '}';
    }
};
using EdgeList = COOMatrix<Edge>;
using AdjacencyList = CSRMatrix<Edge>;
}  // namespace bys

/**
 * @file dijkstra.hpp
 * @brief Dijkstra
 */
namespace bys {
/**
 * @brief ダイクストラ
 *
 * O(Elog(V))
 */
std::vector<ll> dijkstra(const CSRMatrix<Edge>& graph, int source) {
    using Node = std::pair<ll, std::size_t>;
    std::size_t n = graph.size();
    vector<ll> cost(n, LINF);
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
    cost[source] = 0;
    que.push({0, source});

    while (!que.empty()) {
        auto [top_cost, top] = que.top();
        que.pop();
        if (cost[top] < top_cost) continue;
        for (auto&& next : graph[top]) {
            ll next_cost = cost[top] + next.weight;
            if (next_cost < cost[next.dest]) {
                cost[next.dest] = next_cost;
                que.push({next_cost, next.dest});
            }
        }
    }
    return cost;
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
    ll sum() const {
        ll a = it;
        ll b = (stop - dir - it) / step * step + it;
        ll n = (b - a) / step + 1;
        return n > 0 ? (a + b) * n / 2 : 0;
    }

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
    auto [b, k, sx, sy, gx, gy] = scanner.read<ll, 6>();

    auto fsx = sx / b * b;
    auto fsy = sy / b * b;
    auto fgx = gx / b * b;
    auto fgy = gy / b * b;
    vector<Pall> street_s = {
        {fsx, fsy},          //
        {sx, fsy},           //
        {fsx + b, fsy},      //
        {fsx + b, sy},       //
        {fsx + b, fsy + b},  //
        {sx, fsy + b},       //
        {fsx, fsy + b},      //
        {fsx, sy}            //
    };
    vector<Pall> street_g = {
        {fgx, fgy},          //
        {gx, fgy},           //
        {fgx + b, fgy},      //
        {fgx + b, gy},       //
        {fgx + b, fgy + b},  //
        {gx, fgy + b},       //
        {fgx, fgy + b},      //
        {fgx, gy}            //
    };

    EdgeList edges(18);
    for (auto i : irange(1, 8, 2)) {
        {
            auto [ux, uy] = street_s[i];
            auto dist = (abs(ux - sx) + abs(uy - sy)) * k;
            edges.emplace_back(8, i, dist);
            edges.emplace_back(i, 8, dist);
        }
        {
            auto [ux, uy] = street_g[i];
            auto dist = (abs(ux - gx) + abs(uy - gy)) * k;
            edges.emplace_back(8 + 9, i + 9, dist);
            edges.emplace_back(i + 9, 8 + 9, dist);
        }
    }

    for (int i : irange(8)) {
        auto u = i;
        auto v = (i + 1) % 8;
        {
            auto [ux, uy] = street_s[u];
            auto [vx, vy] = street_s[v];
            auto dist = abs(ux - vx) + abs(uy - vy);
            edges.emplace_back(u, v, dist);
            edges.emplace_back(v, u, dist);
        }
        {
            auto [ux, uy] = street_g[u];
            auto [vx, vy] = street_g[v];
            auto dist = abs(ux - vx) + abs(uy - vy);
            edges.emplace_back(u + 9, v + 9, dist);
            edges.emplace_back(v + 9, u + 9, dist);
        }
    }

    for (int u : irange(0, 8, 2)) {
        for (auto v : irange(0, 8, 2)) {
            auto [ux, uy] = street_s[u];
            auto [vx, vy] = street_g[v];
            auto dist = abs(ux - vx) + abs(uy - vy);
            edges.emplace_back(u, v + 9, dist);
            edges.emplace_back(v + 9, u, dist);
        }
    }

    for (int u : irange(1, 8, 2)) {
        for (auto v : irange(1, 8, 2)) {
            auto [ux, uy] = street_s[u];
            auto [vx, vy] = street_g[v];
            if (ux % b == 0 and ux == vx) {
                auto dist = abs(uy - vy);
                edges.emplace_back(u, v + 9, dist);
                edges.emplace_back(v + 9, u, dist);
            }
            if (uy % b == 0 and uy == vy) {
                auto dist = abs(ux - vx);
                edges.emplace_back(u, v + 9, dist);
                edges.emplace_back(v + 9, u, dist);
            }
        }
    }

    auto ans1 = (abs(sx - gx) + abs(sy - gy)) * k;
    auto ans2 = dijkstra(AdjacencyList(edges), 8)[17];
    print(min(ans1, ans2));
}
}  // namespace bys

int main() { return bys::Solver::main(bys::scanner.read<int>()); }
