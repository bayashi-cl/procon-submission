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
using mint = atcoder::modint998244353;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 998244353;
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
        vector<int> prev(n_node, -1);
        std::queue<int> que;
        que.push(start);

        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (int to : graph[from]) {
                if (cost[to] == INF) {
                    prev[to] = from;
                    cost[to] = cost[from] + 1;
                    que.push(to);
                }
            }
        }
        return prev;
    }
};
vector<int> path_finder(int to, Vec prev) {
    vector<int> path;
    while (to != -1) {
        path.push_back(to);
        to = prev[to];
    }
    std::reverse(std::begin(path), std::end(path));
    return path;
}
void solve() {
    auto [n, m, k] = input<int, 3>();
    auto a = input<int>(m);
    for (auto&& e : a) --e;
    VecVec adj(n);
    vector<Pa> edge;
    for (int i = 0; i < n - 1; ++i) {
        auto [u, v] = input<int, 2>();
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge.push_back({min(u, v), max(u, v)});
        // cnt[{min(u, v), max(u, v)}]++;
    }

    BreadthFirstSearch bfs(adj);
    map<Pa, int> cnt;
    for (int i = 0; i < m - 1; ++i) {
        int f = a[i];
        int t = a[i + 1];
        auto p = bfs.search(f);
        Vec path = path_finder(t, p);
        for (int j = 0; j < (int)path.size() - 1; ++j) {
            int p = path[j];
            int q = path[j + 1];
            cnt[{min(p, q), max(p, q)}]++;
        }
    }
    vector<int> v(n - 1);
    for (int i = 0; i < n - 1; ++i) v[i] = cnt[edge[i]];

    vector<map<int, mint>> dp(n);
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (auto [key, val] : dp[i - 1]) {
            dp[i][key + v[i - 1]] += val;
            dp[i][key - v[i - 1]] += val;
        }
    }
    print(dp.back()[k]);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
