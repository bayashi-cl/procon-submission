#include <atcoder/math>
#include <atcoder/modint>
#include <atcoder/segtree>
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
    int n_node;
    vector<int> cost;
    vector<int> tour;
    vector<int> first;

    DeapthFirstSearch(Adj graph)
        : graph(graph), n_node(graph.size()), cost(n_node, -1), first(n_node) {}

    void search(int now, int depth = 0) {
        first[now] = tour.size();
        cost[now] = depth;
        tour.push_back(depth);
        for (int to : graph[now]) {
            if (cost[to] != -1) continue;
            search(to, depth + 1);
            tour.push_back(depth);
        }
    }
};

int op(int a, int b) { return min(a, b); }
int e() { return (int)(1e9); }

void solve() {
    auto n = input<int>();
    VecVec adj(n);
    for (int i = 0; i < n - 1; ++i) {
        auto [x, y] = input<int, 2>();
        --x, --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    DeapthFirstSearch dfs(adj);
    dfs.search(0);
    atcoder::segtree<int, op, e> seg(dfs.tour);

    auto q = input<int>();
    for (int i = 0; i < q; ++i) {
        auto [a, b] = input<int, 2>();
        a--, b--;
        int fa = dfs.first[a];
        int fb = dfs.first[b];
        if (fa > fb) std::swap(fa, fb);
        int ans = dfs.cost[a] + dfs.cost[b] - seg.prod(fa, fb + 1) * 2 + 1;
        print(ans);
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
