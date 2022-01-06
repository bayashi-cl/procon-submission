#line 2 "/home/bayashi/dev/byslib/core/stdlib.hpp"
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
using Pall = pair<ll, ll>;
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
#line 3 "/home/bayashi/dev/byslib/core/io.hpp"

namespace bys {
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
    static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    if (container.empty()) return os;
    std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
//! @brief 任意の型を1つ
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
//! @brief 任意の型がn要素のvector
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
//! @brief 任意の型がn行m列のvector
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
    cin >> res;
    return res;
}

//! @brief 任意の型をN個 受け取りは構造化束縛で
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
//! @brief 2つ以上の異なる型 受け取りは構造化束縛で
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}
//! @brief 標準入力から代入
template <class... Ts>
void cinto(Ts&... args) {
    (cin >> ... >> args);
}
//! @brief pythonのprintっぽい挙動をする
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
    //! @brief 空白区切りで出力
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
    //! @brief 出力後flush インタラクティブ問題用
    template <class... Ts>
    void send(const Ts&... a) {
        operator()(a...);
        os << std::flush;
    }
} print(std::cout), debug(std::cerr);

//! @brief cin高速化など
inline void fastio() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/macro.hpp"

// clang-format off
#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...) debug("[debug] line:", __LINE__, "\t", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
#line 3 "/home/bayashi/dev/byslib/core/solver.hpp"

namespace bys {
struct Solver {
    int IT = 1;
    Solver() { fastio(); }
    void solve();
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/graph/edge.hpp"

namespace bys {
struct Edge {
    int from, to;
    ll cost;

    //! @brief 重みなし単頂点
    Edge(int to) : from(-1), to(to), cost(1) {}
    //! @brief 重み付き単頂点
    Edge(int to, ll cost) : from(-1), to(to), cost(cost) {}
    //! @brief 重み付き両頂点
    Edge(int from, int to, ll cost) : from(from), to(to), cost(cost) {}
    bool operator<(const Edge& rh) const { return cost < rh.cost; }
    friend std::ostream& operator>>(std::ostream& os, const Edge& e) { return os << e.from << " - " << e.to << ": " << e.cost; }
};
using Adj = vector<vector<Edge>>;
using EdgeList = vector<Edge>;
}  // namespace bys
#line 5 "/home/bayashi/dev/byslib/graph/breadth_first.hpp"

namespace bys {
struct BreadthFirstSearch {
    int n_node;
    vector<int> prev;
    vector<int> cost;

    BreadthFirstSearch(const Adj& graph, int start, int err_val = -1)
        : n_node(graph.size()), prev(n_node, -1), cost(n_node, INF) {
        search(graph, start);
        std::replace(cost.begin(), cost.end(), INF, err_val);
    }

    void search(const Adj& graph, int start) {
        cost[start] = 0;
        std::queue<int> que;
        que.push(start);
        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (auto&& to : graph[from]) {
                if (cost[to.to] == INF) {
                    prev[to.to] = from;
                    cost[to.to] = cost[from] + 1;
                    que.push(to.to);
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
struct ZeroOneBFS {
    int n_node;
    vector<int> cost;
    vector<int> prev;

    ZeroOneBFS(Adj& graph, int start, int err_val = -1) : n_node(graph.size()), cost(n_node, INF), prev(n_node, -1) {
        search(graph, start);
        std::replace(cost.begin(), cost.end(), INF, err_val);
    }

    void search(const Adj& graph, int start) {
        std::deque<int> que;
        cost[start] = 0;
        que.push_back(start);
        while (!que.empty()) {
            int now = que.front();
            que.pop_front();
            for (auto&& to : graph[now]) {
                int dist = cost[now] + to.cost;
                if (dist >= cost[to.to]) continue;
                cost[to.to] = dist;
                prev[to.to] = now;
                if (to.cost == 0) {
                    que.push_front(to.to);
                } else {
                    que.push_back(to.to);
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
#line 4 "past202112_k/main.cpp"

namespace bys {
void Solver::solve() {
    auto [n, m, q, k] = input<int, 4>();
    auto a = input<int>(k);
    for (auto&& ai : a) --ai;
    Adj graph(n);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = input<int, 2>();
        --u, --v;
        graph[u].push_back({v});
        graph[v].push_back({u});
    }
    vector<vector<int>> cost;
    for (int i = 0; i < k; ++i) {
        BreadthFirstSearch bfs(graph, a[i]);
        cost.push_back(bfs.cost);
    }
    for (int qi = 0; qi < q; ++qi) {
        auto [s, t] = input<int, 2>();
        --s, --t;
        int ans = INF;
        for (int i = 0; i < k; ++i) {
            chmin(ans, cost[i][s] + cost[i][t]);
        }
        print(ans);
    }
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
