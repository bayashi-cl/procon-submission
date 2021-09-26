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
struct DeapthFirstSearch {
    using Adj = vector<vector<int>>;
    Adj graph;
    vector<int> pre_order;
    vector<int> post_order;
    vector<int> tour;
    vector<bool> seen;

    DeapthFirstSearch(Adj graph) : graph(graph), seen(graph.size()) {}

    void search(int now) {
        seen[now] = true;
        pre_order.push_back(now);
        tour.push_back(now);
        for (int to : graph[now]) {
            if (seen[to]) continue;
            search(to);
            tour.push_back(now);
        }
        post_order.push_back(now);
    }
};
struct BreadthFirstSearch {
    using Adj = vector<vector<int>>;
    Adj graph;
    int n_node;
    vector<int> prev;

    BreadthFirstSearch(Adj graph)
        : graph(graph), n_node(graph.size()), prev(n_node, -1) {}

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
void solve() {
    auto n = input<int>();
    VecVec graph(n);
    for (int i = 0; i < n - 1; ++i) {
        auto [u, v] = input<int, 2>();
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    BreadthFirstSearch bfs(graph);
    auto cost = bfs.search(0);
    vector<ll> ans(n);
    ans[0] = std::accumulate(std::begin(cost), std::end(cost), 0LL);

    DeapthFirstSearch dfs(graph);
    dfs.search(0);
    Vec sub(n);
    for (auto&& now : dfs.post_order) {
        for (auto&& to : graph[now]) {
            sub[now] += sub[to];
        }
        sub[now]++;
    }

    for (auto&& now : dfs.pre_order) {
        for (auto&& to : graph[now]) {
            if (ans[to]) continue;
            ans[to] = ans[now] + n - 2 * sub[to];
        }
    }
    for (auto&& e : ans) print(e);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
