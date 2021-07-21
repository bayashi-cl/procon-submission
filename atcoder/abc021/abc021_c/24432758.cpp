#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
#include <cmath>
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
#include <valarray>
#include <vector>

namespace bys {
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
inline std::istream& operator>>(std::istream& is, mint& m) {ll n; is >> n; m = n; return is;}
inline std::ostream& operator<<(std::ostream& os, const mint& m) { os << m.val(); return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class T> inline T input() {T n; cin >> n; return n;}
template <class T> inline vector<T> input(int n) {vector<T> res(n); for (auto&& r : res) cin >> r; return res;}
template <class T, size_t N> inline std::array<T, N> input() {std::array<T, N> res; for (auto&& r : res) cin >> r; return res;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
}  // namespace bys

namespace bys {

struct BreadthFirstSearch {
    using Adj = vector<vector<int>>;

    Adj graph;
    int n_node;

    BreadthFirstSearch(Adj graph) : graph(graph), n_node(graph.size()) {}

    vector<int> search(int start) {
        vector<int> cost(n_node, INF);
        cost[start] = 0;
        std::queue<int> que;
        que.push(start);

        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (int to : graph[from]) {
                if (cost[to] == INF) {
                    cost[to] = cost[from] + 1;
                    que.push(to);
                }
            }
        }
        return cost;
    }
};
struct DeapthFirstSearch {
    using Adj = vector<vector<int>>;
    Adj graph;
    vector<int> pre_order;
    vector<int> post_order;
    vector<bool> seen;

    DeapthFirstSearch(Adj graph) : graph(graph) { seen.resize(graph.size()); }

    void search(int now) {
        seen[now] = true;
        pre_order.push_back(now);
        for (int to : graph[now]) {
            if (seen[to]) continue;
            search(to);
        }
        post_order.push_back(now);
    }
};

void solve() {
    auto [n, a, b, m] = input<int, 4>();
    a--, b--;
    VecVec adj(n);
    vector<Pa> edge;
    for (int i = 0; i < m; ++i) {
        auto [x, y] = input<int, 2>();
        x--, y--;
        edge.push_back({x, y});
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    BreadthFirstSearch bfs(adj);
    auto cost = bfs.search(a);

    VecVec dag(n);
    for (auto [x, y] : edge) {
        if (cost[x] + 1 == cost[y]) dag[x].push_back(y);
        if (cost[y] + 1 == cost[x]) dag[y].push_back(x);
    }

    DeapthFirstSearch dfs(dag);
    dfs.search(a);
    auto topo = dfs.post_order;
    std::reverse(std::begin(topo), std::end(topo));

    vector<mint> dp(n);
    dp[a] = 1;
    for (auto&& f : topo) {
        for (auto&& t : dag[f]) {
            dp[t] += dp[f];
        }
    }
    print(dp[b]);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
