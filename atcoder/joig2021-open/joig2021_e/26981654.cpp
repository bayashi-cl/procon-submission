#line 2 "byslib/template/bys.hpp"
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
    char sep = ' ', end = '\n';
    Print() : os(std::cout) {}
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
} print, debug(std::cerr);

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
#define EXIT(...)           \
    {                       \
        print(__VA_ARGS__); \
        return;             \
    }
}  // namespace bys
#line 3 "byslib/graph/edge.hpp"

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
#line 4 "byslib/graph/dijkstra.hpp"

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
#line 3 "joig2021_e/main.cpp"

namespace bys {
void solve() {
    auto [n, m, l] = input<int, 3>();
    Adj graph(n * (m + 1));

    for (int i = 0; i < m; ++i) {
        auto [a, b, c] = input<int, 3>();
        --a, --b;
        for (int j = 0; j < m; ++j) {
            graph[a + n * j].push_back(Edge(b + n * j, c));
            graph[b + n * j].push_back(Edge(a + n * (j + 1), c));
        }
    }
    Dijkstra dij(graph, 0, LINF);
    for (int i = 0; i <= m; ++i) {
        if (dij.cost[n - 1 + n * i] <= l) EXIT(i);
    }
    print(-1);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    return 0;
}
