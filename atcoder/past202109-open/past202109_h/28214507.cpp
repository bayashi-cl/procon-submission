#line 2 "/home/bayashi/dev/byslib/byslib/template/bys.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
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
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;

// const
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;

// I/O
// pair
template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
    return is >> p.first >> p.second;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << p.first << " " << p.second;
}

// STL container
struct is_container_impl {
    template <typename T>
    static auto check(T&& obj)
        -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container
    : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    if (container.empty()) return os;
    std::for_each(std::begin(container), std::prev(std::end(container)),
                  [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container),
                  [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
    cin >> res;
    return res;
}
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}

struct Print {
    std::ostream& os;
    string sep = " ", end = "\n";
    Print(std::ostream& os) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T>
    void operator()(const T& a) {
        os << a << end;
    }
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
    template <class... Ts>
    void send(const Ts&... a) {
        operator()(a...);
        os << std::flush;
    }
} print(std::cout), debug(std::cerr);

// utility
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
template <class T>
inline T iceil(T a, T b) {
    return (a + b - 1) / b;
}
inline bool pop(int s, int d) { return s & (1 << d); }
inline bool pop(ll s, int d) { return s & (1LL << d); }
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1)
        : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
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

// config
inline void init() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

// macro
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
// clang-format off
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on

// solver
struct Solver {
    Solver() { init(); }
    void solve();
    void solve(int rep) {
        for (int i = 0; i < rep; ++i) solve();
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/byslib/graph/edge.hpp"

namespace bys {
struct Edge {
    int from, to;
    ll cost;
    // 重みなし単頂点
    Edge(int to) : from(-1), to(to), cost(1) {}
    // 重み付き単頂点
    Edge(int to, ll cost) : from(-1), to(to), cost(cost) {}
    // 重み付き両頂点
    Edge(int from, int to, ll cost) : from(from), to(to), cost(cost) {}
    bool operator<(const Edge& rh) const { return cost < rh.cost; }
    friend std::ostream& operator>>(std::ostream& os, const Edge& e) {
        return os << e.from << " - " << e.to << ": " << e.cost;
    }
};
using Adj = vector<vector<Edge>>;
}  // namespace bys
#line 4 "/home/bayashi/dev/byslib/byslib/graph/depth_first.hpp"

namespace bys {
struct DepthFirstSearch {
    const Adj& graph;
    int n_node;
    vector<int> cost;
    vector<int> pre_order;
    vector<int> post_order;
    vector<int> tour;
    vector<int> prev;

    DepthFirstSearch(const Adj& graph, int start)
        : graph(graph),
          n_node(graph.size()),
          cost(n_node, -1),
          prev(n_node, -1) {
        cost[start] = 0;
        search(start);
    }
    DepthFirstSearch(const Adj& graph)
        : graph(graph),
          n_node(graph.size()),
          cost(n_node, -1),
          prev(n_node, -1) {}

    void crawl() {
        for (int i = 0; i < n_node; ++i) {
            if (cost[i] == -1) {
                cost[i] = 0;
                search(i);
            }
        }
    }

    void search(int now) {
        // cost[now] = true;
        pre_order.push_back(now);
        tour.push_back(now);
        for (auto&& to : graph[now]) {
            if (cost[to.to] != -1) continue;
            cost[to.to] = cost[now] + 1;
            prev[to.to] = now;
            search(to.to);
            tour.push_back(now);
        }
        post_order.push_back(now);
    }
    vector<int> path(int to) {
        assert(to < n_node);
        vector<int> res;
        while (to != -1) {
            res.push_back(to);
            to = prev[to];
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
}  // namespace bys
#line 4 "/home/bayashi/dev/byslib/byslib/graph/dijkstra.hpp"

namespace bys {
struct Dijkstra {
    int n_node;
    vector<int> prev;
    vector<ll> cost;

    Dijkstra(const Adj& graph, int start, ll err_val = -1)
        : n_node(graph.size()), prev(n_node, -1), cost(n_node, LINF) {
        search(graph, start);
        std::replace(cost.begin(), cost.end(), LINF, err_val);
    }

    void search(const Adj& graph, int start) {
        using Node = std::pair<ll, int>;
        std::priority_queue<Node, vector<Node>, std::greater<Node>> que;
        cost[start] = 0;
        que.push({0, start});
        while (!que.empty()) {
            auto top = que.top();
            que.pop();
            if (cost[top.second] < top.first) continue;
            for (auto&& next : graph[top.second]) {
                ll next_cost = cost[top.second] + next.cost;
                if (next_cost < cost[next.to]) {
                    cost[next.to] = next_cost;
                    prev[next.to] = top.second;
                    que.push({next_cost, next.to});
                }
            }
        }
    }
    vector<int> path(int to) {
        assert(to < n_node);
        vector<int> res;
        while (to != -1) {
            res.push_back(to);
            to = prev[to];
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
}  // namespace bys
#line 4 "past202109_h/main.cpp"

namespace bys {
struct LowestCommonAncestor {
    const Adj& graph;
    const int n_node;
    DepthFirstSearch dfs;
    vector<vector<int>> parent;
    int log_size = 1;

    LowestCommonAncestor(const Adj& graph, int root = 0)
        : graph(graph), n_node(graph.size()), dfs(graph, root) {
        // DepthFirstSearch dfs(graph, root);
        // int k = 1;
        while ((1 << log_size) < n_node) ++log_size;
        parent.assign(log_size, vector<int>(n_node, -1));
        parent[0] = dfs.prev;
        for (int i = 0; i < log_size - 1; i++) {
            for (int j = 0; j < n_node; j++) {
                if (parent[i][j] < 0) {
                    parent[i + 1][j] = -1;
                } else {
                    parent[i + 1][j] = parent[i][parent[i][j]];
                }
            }
        }
    }
    int prev(int n, int x) const {
        // nのx個上
        for (int k = 0; k < log_size; k++) {
            if (x >> k & 1) n = parent[k][n];
        }
        return n;
    }
    int lca(int a, int b) const {
        if (dfs.cost[a] < dfs.cost[b]) std::swap(a, b);
        a = prev(a, dfs.cost[a] - dfs.cost[b]);
        if (a == b) return a;
        for (int k = log_size - 1; k >= 0; k--) {
            if (parent[k][a] != parent[k][b]) {
                a = parent[k][a];
                b = parent[k][b];
            }
        }
        return parent[0][a];
    }
};
void Solver::solve() {
    auto [n, x] = input<int, 2>();
    Adj graph(n);
    for (int i = 0; i < n - 1; ++i) {
        auto [a, b, c] = input<int, 3>();
        --a, --b;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    Dijkstra dij(graph, 0);
    LowestCommonAncestor lca(graph);
    for (int i : Range(n)) {
        for (int j : Range(i + 1, n)) {
            ll d = dij.cost[i] + dij.cost[j] - 2 * dij.cost[lca.lca(i, j)];
            if (d == x) EXIT("Yes");
        }
    }
    print("No");
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
