#include <atcoder/dsu>
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
};
void solve() {
    int h, w;
    cin >> h >> w;
    auto s = input<string>(h);
    auto idx = [&](int i, int j) { return i * w + j; };
    auto contain = [&](int i, int j) {
        return 0 <= i && i < h && 0 <= j && j < w;
    };
    vector<Pa> delta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<Pa> punch;
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            if (abs(i) == 2 && abs(j) == 2) continue;
            punch.push_back({i, j});
        }
    }
    Dijkstra::Adj adj(h * w);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int f = idx(i, j);
            for (auto [di, dj] : delta) {
                int ni = i + di, nj = j + dj;
                if (!contain(ni, nj)) continue;
                if (s[ni][nj] == '.') {
                    int t = idx(ni, nj);
                    adj[f].push_back({0, t});
                }
            }

            for (auto [di, dj] : punch) {
                int ni = i + di, nj = j + dj;
                if (!contain(ni, nj)) continue;
                int t = idx(ni, nj);
                adj[f].push_back({1, t});
            }
        }
    }
    Dijkstra dij(adj);
    dij.search(0);
    print(dij.cost[h * w - 1]);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
