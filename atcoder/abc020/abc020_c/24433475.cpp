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

template <typename T, class Lambda, class... Args>
T meguru_bisect(T ok, T ng, Lambda is_ok, Args... args) {
    assert(is_ok(ok, args...));
    assert(!is_ok(ng, args...));

    while (std::abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        if (is_ok(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

void solve() {
    int h, w, t;
    cin >> h >> w >> t;
    auto s = input<string>(h);
    vector<Pa> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<pair<int, Pa>> edge;
    int start, goal;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int from = i * w + j;
            if (s[i][j] == 'S') start = from;
            if (s[i][j] == 'G') goal = from;
            for (auto [di, dj] : delta) {
                if (i + di < 0 || h <= i + di) continue;
                if (j + dj < 0 || w <= j + dj) continue;
                int to = (i + di) * w + j + dj;
                if (s[i + di][j + dj] == '#') {
                    edge.push_back({0, {from, to}});
                } else {
                    edge.push_back({1, {from, to}});
                }
            }
        }
    }

    auto is_ok = [&](int x) {
        Dijkstra::Adj adj(h * w);
        for (auto [t, node] : edge) {
            if (t == 0) {
                adj[node.first].push_back({x, node.second});
            } else {
                adj[node.first].push_back({1, node.second});
            }
        }
        Dijkstra dij(adj);
        dij.search(start);
        return dij.cost[goal] <= t;
    };

    print(meguru_bisect(1, t + 1, is_ok));
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
