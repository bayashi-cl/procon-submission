#line 2 "/home/bayashi/dev/byslib/acl/acl.hpp"
#include <iostream>
#include <atcoder/math>
#include <atcoder/modint>

namespace bys {
using atcoder::pow_mod, atcoder::inv_mod;
using mint = atcoder::modint998244353;
using mint7 = atcoder::modint1000000007;
template <int MOD>
inline std::istream& operator>>(std::istream& is, atcoder::static_modint<MOD>& m) {
    long long int n;
    is >> n;
    m = n;
    return is;
}
template <typename T, typename std::enable_if_t<atcoder::internal::is_modint<T>::value, std::nullptr_t> = nullptr>
std::ostream& operator<<(std::ostream& os, const T& m) {
    return os << m.val();
}
}  // namespace bys
#line 2 "/home/bayashi/dev/byslib/core/stdlib.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iomanip>
#line 14 "/home/bayashi/dev/byslib/core/stdlib.hpp"
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
#line 3 "/home/bayashi/dev/byslib/core/const.hpp"

namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
#line 4 "/home/bayashi/dev/byslib/core/types.hpp"
#include <utility>

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
#line 4 "/home/bayashi/dev/byslib/core/printer.hpp"

namespace bys {
struct Printer {
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
    template <class... Ts>
    void operator()(Ts&&... args) {
        print(std::forward<Ts>(args)...);
    }

    void flush() { os << std::flush; }
    template <class... Ts>
    void send(Ts&&... args) {
        print(std::forward<Ts>(args)...);
        flush();
    }

    Printer set(string sep_ = " ", string end_ = "\n") {
        _sep = sep_;
        _end = end_;
        return *this;
    }
    void lf() { cat(_end); }

   private:
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
};
}  // namespace bys
#line 4 "/home/bayashi/dev/byslib/core/scanner.hpp"

namespace bys {
struct Scanner {
    Scanner(std::istream& is_) : is(is_){};

    template <class... Ts>
    void scan(Ts&... args) {
        (is >> ... >> args);
    }

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

    template <class T, std::size_t N, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    std::array<R, N> read() {
        std::array<R, N> res;
        for (auto&& e : res) e = read<T>();
        return res;
    }

    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<R> readvec(int n) {
        vector<R> res(n);
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<vector<R>> readvec(int n, int m) {
        vector<vector<R>> res(n);
        for (auto&& e : res) e = readvec<T>(m);
        return res;
    }

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
    std::string getline(bool skip_ws = true) {
        if (skip_ws) std::ws(is);
        std::string res;
        std::getline(is, res);
        return res;
    }

   private:
    std::istream& is;
    template <class Tp, std::size_t... I>
    inline decltype(auto) read_tuple(std::index_sequence<I...>) {
        return Tp{read<typename std::tuple_element_t<I, Tp>>()...};
    }
};
}  // namespace bys
#line 5 "/home/bayashi/dev/byslib/core/io.hpp"

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
#line 2 "/home/bayashi/dev/byslib/core/macro.hpp"
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
#line 2 "/home/bayashi/dev/byslib/core/solver.hpp"

namespace bys {
struct Solver {
    int IT = 1;
    Solver() {}
    void solve();
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/graphv2/edge.hpp"
namespace bys {
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
struct AdjacencyList {
    AdjacencyList(std::size_t n, std::size_t m) : _n(n), _m(m), index(n + 1), _build_flg(m == 0) { buf.reserve(m); }

    struct AdjacencyRange {
        using iterator = std::vector<Edge>::const_iterator;
        using reference = std::vector<Edge>::const_reference;
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
        data.resize(_m);
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
    std::size_t n_edge() const { return _m; }
    bool build_flg() const { return _build_flg; }

   private:
    std::size_t _n, _m;
    std::vector<Edge> buf, data;
    std::vector<std::size_t> index;
    bool _build_flg;
};
}  // namespace bys
#line 5 "/home/bayashi/dev/byslib/graphv2/reader.hpp"
namespace bys {
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
AdjacencyList read_tree_uv(std::size_t n, bool directed = false, int index = 1) { return read_adj_uv(n, n - 1, directed, index); }
AdjacencyList read_tree_uvc(std::size_t n, bool directed = false, int index = 1) {
    return read_adj_uvc(n, n - 1, directed, index);
}
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
#line 2 "/home/bayashi/dev/byslib/utility/change.hpp"
namespace bys {
template <class T>
inline bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline bool chmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/utility/fixpoint.hpp"
namespace bys {
template <typename F>
struct FixPoint : F {
    FixPoint(F&& f) : F{std::forward<F>(f)} {}
    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};
template <typename F>
inline FixPoint<std::decay_t<F>> fix(F&& f) {
    return std::forward<std::decay_t<F>>(f);
}
}  // namespace bys
#line 2 "/home/bayashi/dev/byslib/utility/range.hpp"

namespace bys {
//! @brief pythonのrangeと同じ挙動
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1) : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
    Range(T stop) : it(0), stop(stop), step(1), dir(1) {}
    Range<T> begin() const { return *this; }
    T end() const { return stop; }
    bool operator!=(const T val) const { return (val - it) * dir > 0; }
    void operator++() { it += step; }
    const T& operator*() const { return it; }

   private:
    T it;
    const T stop, step;
    const int dir;

    friend Range reversed(const Range& r) {
        auto new_start = (r.stop - r.dir - r.it) / r.step * r.step + r.it;
        return {new_start, r.it - r.dir, -r.step};
    }
};
template <class T>
Range<T> irange(T stop) {
    return Range(stop);
}
template <class T>
Range<T> irange(T start, T stop, T step = 1) {
    return Range(start, stop, step);
}
}  // namespace bys
#line 7 "abc133_e/main.cpp"

namespace bys {
void Solver::solve() {
    const auto [n, k] = scanner.read<int, 2>();
    auto graph = read_tree_uv(n);
    assert(graph.build_flg());

    FixPoint dfs([&](auto&& self, int now, int prev, int col) -> mint7 {
        mint7 res = col;
        int used = prev == -1 ? 1 : 2;

        for (auto&& nxt : graph[now]) {
            if ((int)nxt.dest == prev) continue;
            res *= self(nxt.dest, now, k - used);
            used++;
        }
        return res;
    });

    print(dfs(0, -1, k));
    // DepthFirstSearch dfs(graph, 0);
    // MultiComb mc(k);
    // vector<mint7> dp(n);
    // for (auto&& now : dfs.post_order) {
    //     int col = k - 1;
    //     int child = 0;
    //     mint7 prod = 1;
    //     for (auto&& nxt : graph[now]) {
    //         if ((int)nxt.dest == dfs.prev[now]) {
    //             --col;
    //             continue;
    //         }
    //         ++child;
    //         prod *= dp[nxt];
    //     }
    //     dp[now] = prod * mc.perm(col, child);
    // }
    // print(dp[0] * k);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
