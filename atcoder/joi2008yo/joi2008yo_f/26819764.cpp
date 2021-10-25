#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <atcoder/math>
#include <atcoder/modint>
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
// clang-format off
using atcoder::pow_mod, atcoder::inv_mod;
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;
using mint = atcoder::modint998244353;
using ll = long long int;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T> using uset = std::unordered_set<T>;
template <class S, class T> using umap = std::unordered_map<S, T>;
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
inline std::istream& operator>>(std::istream& is, mint& m) { ll n; is >> n; m = n; return is; }
inline std::ostream& operator<<(std::ostream& os, const mint& m) { return os << m.val(); }
template <class T, class U> std::istream& operator>>(std::istream& is, std::pair<T, U>& p) { return is >> p.first >> p.second; }
template <typename T, typename U> std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) { return os << p.first << " " << p.second; }
struct is_container_impl { template <typename T> static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{}); template <typename T> static auto check(...) -> std::false_type; };
template <typename T> class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept { std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; }); return os << *std::prev(std::end(container)); }
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) { std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; }); return is; }
template <class T> inline T input() { T n; cin >> n; return n; }
template <class T> inline vector<T> input(int n) { vector<T> res(n); cin >> res; return res; }
template <class T, size_t N> inline std::array<T, N> input() { std::array<T, N> res; cin >> res; return res; }
template <class S, class T, class... Us> std::tuple<S, T, Us...> input() { std::tuple<S, T, Us...> res; std::apply([](auto&... e) { (cin >> ... >> e); }, res); return res; }
struct Print {
    std::ostream& os;
    char sep = ' ', end = '\n';
    Print(std::ostream& os = std::cout) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T> void operator()(const T& a) { os << a << end; }
    template <class T, class... Ts> void operator()(const T& a, const Ts&... b) { os << a; (os << ... << (os << sep, b)); os << end; }
} print, debug(std::cerr);
template <class T> inline bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
template <class T> inline bool chmin(T& a, const T& b) { if (b < a) { a = b; return 1; } return 0; }
template <class T> inline T ceil(T a, T b) { return (a + b - 1) / b; }
inline bool pop(int s, int d) { return s & (1 << d); }
inline void init() { cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11); std::cerr << std::boolalpha; }
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
}  // namespace bys

namespace bys {
struct Dijkstra {
    using Edge = std::pair<ll, int>;  // (cost, node)
    using Adj = vector<vector<Edge>>;
    Adj graph;
    vector<ll> cost;
    vector<int> prev;
    int n_node;

    Dijkstra(const Adj& graph) : graph(graph) {
        n_node = graph.size();
        cost.resize(n_node, LINF);
        prev.resize(n_node, -1);
    }

    /**
     * @brief 探索
     * コストはself.costに格納される。
     * @param start 探索開始点
     */
    void search(int start) {
        std::priority_queue<Edge, vector<Edge>, std::greater<Edge>> que;
        cost[start] = 0;
        que.push(Edge(0, start));

        while (!que.empty()) {
            auto [top_cost, top_node] = que.top();
            que.pop();
            if (cost[top_node] < top_cost) continue;
            for (auto [adj_cost, adj_node] : graph[top_node]) {
                ll temp_cost = cost[top_node] + adj_cost;
                if (temp_cost < cost[adj_node]) {
                    cost[adj_node] = temp_cost;
                    prev[adj_node] = top_node;
                    que.push(Edge(temp_cost, adj_node));
                }
            }
        }
    }

    /**
     * @brief 経路復元
     * @param to
     * @return vector<int>
     */
    vector<int> path_finder(int to) {
        assert(to <= n_node);
        vector<int> path;
        while (to != -1) {
            path.push_back(to);
            to = prev[to];
        }
        std::reverse(std::begin(path), std::end(path));
        return path;
    }

    ll get_cost(int i) {
        ll res = cost[i];
        if (res == LINF) res = -1;
        return res;
    }
};

void solve() {
    auto [n, k] = input<int, 2>();
    Dijkstra::Adj graph(n);
    for (int i = 0; i < k; ++i) {
        auto com = input<int>();
        if (com == 0) {
            auto [a, b] = input<int, 2>();
            --a, --b;
            Dijkstra dij(graph);
            dij.search(a);
            ll ans = dij.cost[b];
            if (ans == LINF) ans = -1;
            print(ans);
        } else {
            auto [c, d, e] = input<int, 3>();
            --c, --d;
            graph[c].push_back({e, d});
            graph[d].push_back({e, c});
        }
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    return 0;
}
