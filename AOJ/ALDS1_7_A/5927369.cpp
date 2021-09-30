#include <cassert>
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
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
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
                    prev[to] = from;
                    cost[to] = cost[from] + 1;
                    que.push(to);
                }
            }
        }
        return cost;
    }
};
template <class T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
    os << "[";
    for (std::size_t i = 0; i < vec.size(); i++) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}
void solve() {
    auto n = input<int>();
    map<int, Vec> c;
    set<int> ch;
    for (int i = 0; i < n; ++i) ch.insert(i);
    VecVec adj(n);
    for (int i = 0; i < n; ++i) {
        auto f = input<int>();
        auto k = input<int>();
        auto t = input<int>(k);
        c[f] = t;
        for (auto&& ti : t) {
            ch.erase(ti);
            adj[f].push_back(ti);
            adj[ti].push_back(f);
        }
    }
    int root = *ch.begin();
    BreadthFirstSearch bfs(adj);
    auto depth = bfs.search(root);

    for (int i = 0; i < n; ++i) {
        cout << "node " << i << ": ";
        cout << "parent = " << bfs.prev[i] << ", ";
        cout << "depth = " << depth[i] << ", ";
        if (i == root) {
            cout << "root, ";
        } else if (c[i].empty()) {
            cout << "leaf, ";
        } else {
            cout << "internal node, ";
        }
        cout << c[i] << endl;
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}

