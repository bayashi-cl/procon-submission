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
 * @file edge.hpp
 * @brief Edge
 * @todo concept
 */
namespace bys {
//! @brief 辺
struct Edge {
    std::size_t src, dest;
    ll weight;
    Edge() {}
    Edge(std::size_t src, std::size_t dest, ll weight = 1) : src(src), dest(dest), weight(weight) {}
    bool operator<(const Edge& rh) const { return weight < rh.weight; }
    operator int() const { return dest; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        return os << "{" << e.src << " -> " << e.dest << ": " << e.weight << "}";
    }
};
//! @brief 隣接リスト
struct DynamicAdjacencyList {
    std::vector<std::vector<Edge>> data;
    DynamicAdjacencyList(std::size_t n) : data(n, vector<Edge>()), _n(n) {}
    std::vector<vector<Edge>>::reference operator[](std::size_t i) { return *(data.begin() + i); }
    const std::vector<vector<Edge>>::const_reference operator[](std::size_t i) const { return *(data.cbegin() + i); }
    void add_edge(const Edge& e) { data[e.src].push_back(e); }
    void add_edge(std::size_t src, std::size_t dest, ll weight = 1) { data[src].push_back({src, dest, weight}); }
    std::size_t size() const { return _n; }

   private:
    std::size_t _n;
};
/**
 * @brief 隣接リスト
 *
 * CSR形式
 * See: https://qiita.com/Nachia/items/d420c08b333296f54526
 */
struct AdjacencyList {
    AdjacencyList(std::size_t n, std::size_t m = UINT64_MAX) : _n(n), _m(m), index(n + 1), _build_flg(m == 0) {}

    struct AdjacencyRange {
        using iterator = std::vector<Edge>::const_iterator;
        using reference = std::vector<Edge>::const_reference;
        using value_type = Edge;
        iterator _begin, _end;
        iterator begin() const { return _begin; }
        iterator end() const { return _end; }
        reference operator[](std::size_t i) const { return *(_begin + i); }
        std::size_t size() const { return std::distance(_begin, _end); }
        bool empty() const { return size() == 0; }
    };
    AdjacencyRange operator[](std::size_t i) const {
        return AdjacencyRange{data.begin() + index[i], data.begin() + index[i + 1]};
    }

    void build() {
        std::partial_sum(index.begin(), index.end(), index.begin());
        data.resize(buf.size());
        for (auto&& e : buf) data[--index[e.src]] = e;
        _build_flg = true;
    }
    void add_edge(const Edge& e) {
        ++index[e.src];
        buf.emplace_back(e);
        if (buf.size() == _m) build();
    }
    void add_edge(std::size_t src, std::size_t dest, ll weight = 1) { add_edge(Edge(src, dest, weight)); }
    std::size_t size() const { return _n; }
    std::size_t n_edge() const { return buf.size(); }
    bool build_flg() const { return _build_flg; }

   private:
    std::size_t _n, _m;
    std::vector<Edge> buf, data;
    std::vector<std::size_t> index;
    bool _build_flg;
};
}  // namespace bys
/**
 * @file depth_first_search.hpp
 * @brief Depth First Search
 *
 * 深さ優先探索
 */
namespace bys {
template <class Adj>
class DepthFirstSearch {
    const Adj& _graph;
    const std::size_t _n;

   public:
    std::vector<int> prev, cost;
    std::vector<std::size_t> pre_order, post_order, euler_tour;
    DepthFirstSearch(const Adj& graph, std::size_t root) : _graph(graph), _n(graph.size()), prev(_n, -1), cost(_n, -1) {
        pre_order.reserve(_n);
        post_order.reserve(_n);
        euler_tour.reserve(2 * _n - 1);
        cost[root] = 0;
        search(root);
    }
    DepthFirstSearch(const Adj& graph) : _graph(graph), _n(graph.size()), prev(_n, -1), cost(_n, -1) {
        pre_order.reserve(_n);
        post_order.reserve(_n);
        euler_tour.reserve(2 * _n - 1);
    }

    void crawl() {
        for (std::size_t i = 0; i < _n; ++i) {
            if (cost[i] == -1) {
                cost[i] = 0;
                search(i);
            }
        }
    }
    void search(std::size_t now) {
        pre_order.emplace_back(now);
        euler_tour.emplace_back(now);
        for (auto&& next : _graph[now]) {
            if (cost[next] != -1) continue;
            cost[next] = cost[now] + 1;
            prev[next] = now;
            search(next.dest);
            euler_tour.emplace_back(now);
        }
        post_order.emplace_back(now);
    }
};
}  // namespace bys
/**
 * @file lca.hpp
 * @brief Lowest Common Ancestor
 *
 * 最近共通祖先
 */
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
 * @file sparse_table.hpp
 * @brief Sparse Table
 */
namespace bys {
/**
 * @brief Sparse Table
 *
 * 構築: O(NlogN)
 * クエリ: O(1)
 * See: https://ikatakos.com/pot/programming_algorithm/data_structure/sparse_table
 *
 * @tparam Band モノイドで冪等性があるもの
 */
template <class Band>
class SparseTable {
    using T = typename Band::set_type;
    int n;
    std::vector<int> lookup;
    std::vector<std::vector<T>> table;

   public:
    SparseTable() {}
    SparseTable(const std::vector<T>& v) { build(v); }

    void build(const std::vector<T>& v) {
        n = v.size();
        lookup.resize(n + 1);

        for (int i = 2; i < n + 1; ++i) lookup[i] = lookup[i >> 1] + 1;
        int max_k = lookup.back();
        table.assign(max_k + 1, std::vector<T>(n));
        std::copy(v.begin(), v.end(), table[0].begin());
        for (int i = 1; i <= max_k; ++i) {
            for (int j = 0; j <= n - (1 << i); ++j) {
                table[i][j] = Band::operation(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int w = r - l;
        return Band::operation(table[lookup[w]][l], table[lookup[w]][r - (1 << lookup[w])]);
    }
};
}  // namespace bys
/**
 * @file fixpoint.hpp
 * @brief FixPoint
 */
namespace bys {
/**
 * @brief ラムダ再帰
 *
 * See: https://koturn.hatenablog.com/entry/2018/06/10/060000
 */
template <typename F>
struct FixPoint : F {
    FixPoint(F&& f) : F{std::forward<F>(f)} {}
    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};
}  // namespace bys
namespace bys {
/**
 * @brief 最近共通祖先
 *
 * Sparse TableによるEulerTour + RmQ
 * 構築   O(N logN)
 * クエリ O(1)
 */
class LowestCommonAncestor {
    struct Vertex {
        int id, depath;
        bool operator<(const Vertex& rh) const { return depath < rh.depath; }
    };
    std::size_t n;
    SparseTable<Min<Vertex>> st;
    std::vector<int> pos;

   public:
    template <class Adj>
    LowestCommonAncestor(const Adj& graph, int root) : n(graph.size()), pos(n) {
        std::vector<Vertex> euler_tour;
        euler_tour.reserve(2 * n - 1);
        FixPoint([&](auto&& self, int now, int prev, int deapth) -> void {
            pos[now] = euler_tour.size();
            euler_tour.push_back({now, deapth});

            for (auto&& nxt : graph[now]) {
                if (int(nxt.dest) == prev) continue;
                self(nxt.dest, now, deapth + 1);
                euler_tour.push_back({now, deapth});
            }
        })(root, -1, 0);
        st.build(euler_tour);
    }
    int lca(std::size_t a, std::size_t b) {
        assert(a < n);
        assert(b < n);
        if (a == b) return a;
        if (pos[a] > pos[b]) std::swap(a, b);
        return st.query(pos[a], pos[b]).id;
    }
};
}  // namespace bys
/**
 * @file reader.hpp
 * @brief Reader
 *
 * グラフ入力
 */
namespace bys {
//! @brief 重みなし隣接リスト
AdjacencyList read_adj_uv(std::size_t n, std::size_t m, bool directed = false, int index = 1) {
    AdjacencyList graph(n, directed ? m : 2 * m);
    for (std::size_t i = 0; i < m; ++i) {
        auto [u, v] = scanner.read<int, 2>();
        u -= index;
        v -= index;
        graph.add_edge(u, v);
        if (!directed) graph.add_edge(v, u);
    }
    return graph;
}
//! @brief 重みつき隣接リスト
AdjacencyList read_adj_uvc(std::size_t n, std::size_t m, bool directed = false, int index = 1) {
    AdjacencyList graph(n, directed ? m : 2 * m);
    for (std::size_t i = 0; i < m; ++i) {
        auto [u, v, c] = scanner.read<int, int, ll>();
        u -= index;
        v -= index;
        graph.add_edge(u, v, c);
        if (!directed) graph.add_edge(v, u, c);
    }
    return graph;
}
//! @brief 重みなし隣接リスト（木）
AdjacencyList read_tree_uv(std::size_t n, bool directed = false, int index = 1) { return read_adj_uv(n, n - 1, directed, index); }
//! @brief 重みつき隣接リスト（木）
AdjacencyList read_tree_uvc(std::size_t n, bool directed = false, int index = 1) {
    return read_adj_uvc(n, n - 1, directed, index);
}
//! @brief 重みなし辺リスト
vector<Edge> read_elist_uv(std::size_t m, int index = 1) {
    vector<Edge> elist;
    elist.reserve(m);
    for (std::size_t i = 0; i < m; ++i) {
        auto [u, v] = scanner.read<int, 2>();
        u -= index;
        v -= index;
        elist.emplace_back(Edge(u, v, 1));
    }
    return elist;
}
//! @brief 重みつき辺リスト
vector<Edge> read_elist_uvc(std::size_t m, int index = 1) {
    vector<Edge> elist;
    elist.reserve(m);
    for (std::size_t i = 0; i < m; ++i) {
        auto [u, v, c] = scanner.read<int, int, ll>();
        u -= index;
        v -= index;
        elist.emplace_back(Edge(u, v, c));
    }
    return elist;
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
    auto [n, k] = scanner.read<int, 2>();
    auto [x, y] = scanner.read<Int1, 2>();
    auto a_ = scanner.readvec<Int1>(k);
    std::set<int> a(a_.begin(), a_.end());
    auto aa = a;
    auto graph = read_tree_uv(n);
    LowestCommonAncestor lca(graph, x);
    DepthFirstSearch dfs(graph, x);

    int prev = x;
    int tot = 0;
    for (auto now : dfs.euler_tour) {
        if (auto itr = a.find(now); itr != a.end()) {
            a.erase(itr);
            auto l = lca.lca(prev, now);
            tot += dfs.cost[prev] + dfs.cost[now] - dfs.cost[l] * 2;
            prev = now;
        }
    }
    tot += dfs.cost[prev];
    int ans = INF;
    for (auto last : aa) {
        if (last == y) {
            DEBUG(dfs.cost[last]);
            chmin(ans, tot - dfs.cost[last]);
        } else {
            auto d = dfs.cost[last] + dfs.cost[y] - dfs.cost[lca.lca(last, y)] * 2;
            chmin(ans, tot - dfs.cost[last] + d);
        }
    }
    print(ans);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(bys::scanner.read<int>());
    return 0;
}
