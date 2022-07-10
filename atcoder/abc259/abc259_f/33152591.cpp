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
    std::vector<int> prev;
    std::vector<ll> cost;
    std::vector<std::size_t> pre_order, post_order, euler_tour;
    DepthFirstSearch(const Adj& graph, std::size_t root) : _graph(graph), _n(graph.size()), prev(_n, -1), cost(_n, LINF) {
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
            if (cost[next] != LINF) continue;
            cost[next] = cost[now] + next.weight;
            prev[next] = now;
            search(next.dest);
            euler_tour.emplace_back(now);
        }
        post_order.emplace_back(now);
    }

    ll dist(std::size_t s, std::size_t t, std::size_t lca) {
        assert(cost[s] != LINF);
        assert(cost[t] != LINF);
        assert(cost[lca] != LINF);
        return cost[s] + cost[t] - 2 * cost[lca];
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
 * @file rooted_tree.hpp
 * @brief Rooted tree
 */
namespace bys {
//! @brief 根付き木に変換
template <class Adj>
AdjacencyList make_rooted(const Adj& graph, int root) {
    auto n = graph.size();
    std::vector<bool> seen(n);
    AdjacencyList res(n, graph.n_edge() / 2);
    vector<int> stack({root});
    while (!stack.empty()) {
        auto now = stack.back();
        stack.pop_back();
        seen[now] = true;
        for (auto&& nxt : graph[now]) {
            if (seen[nxt.dest]) continue;
            res.add_edge(nxt);
            stack.push_back(nxt.dest);
        }
    }
    return res;
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
    auto n = scanner.read<int>();
    auto d = scanner.readvec<int>(n);
    auto graph = read_tree_uvc(n);

    auto rooted = make_rooted(graph, 0);
    DepthFirstSearch dfs(graph, 0);
    vector<Pall> dp(n);

    for (auto now : dfs.post_order) {
        vector<pair<ll, int>> ws;
        for (auto&& nxt : rooted[now]) {
            auto add = d[nxt.dest] == 0 ? -LINF : nxt.weight + dp[nxt.dest].first - dp[nxt.dest].second;
            ws.push_back({add, nxt.dest});
        }
        sort(ws.begin(), ws.end(), std::greater<Pall>());
        for (int i : irange(ws.size())) {
            auto [add, dest] = ws[i];
            if (add >= 0 and i < d[now] - 1) {
                dp[now].first += dp[dest].second + add;
            } else {
                dp[now].first += dp[dest].second;
            }
            if (add >= 0 and i < d[now]) {
                dp[now].second += dp[dest].second + add;
            } else {
                dp[now].second += dp[dest].second;
            }
        }
    }
    print(max(dp[0].first, dp[0].second));
}
}  // namespace bys

int main() { return bys::Solver::main(/* bys::scanner.read<int>() */); }
