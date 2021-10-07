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
struct ZeroOneBFS {
    using Adj = vector<vector<pair<int, int>>>;

    Adj graph;
    int n_node;

    ZeroOneBFS(Adj& adj) : graph(adj), n_node(graph.size()) {}

    vector<int> search(int start) {
        std::deque<int> que;
        vector<int> cost(n_node, INF);
        cost[start] = 0;
        que.push_back(start);
        while (!que.empty()) {
            int now = que.front();
            que.pop_front();
            for (auto [zo, to] : graph[now]) {
                int dist = cost[now] + zo;
                if (dist >= cost[to]) continue;
                cost[to] = dist;
                if (zo == 0) {
                    que.push_front(to);
                } else {
                    que.push_back(to);
                }
            }
        }
        return cost;
    }
};
struct Board {
    int h, w;
    const vector<pair<int, int>> delta = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Board(int row, int col) : h(row), w(col) {}

    bool contain(int row, int col) {
        return 0 <= row && row < h && 0 <= col && col < w;
    }
    vector<pair<int, int>> next(int i, int j) {
        vector<pair<int, int>> res;
        for (auto [di, dj] : delta) {
            int ni = i + di;
            int nj = j + dj;
            if (contain(ni, nj)) res.push_back({ni, nj});
        }
        return res;
    }
    int index(int i, int j) { return i * w + j; }
    int area() { return h * w; }
};
void solve() {
    auto [h, w, ch, cw, dh, dw] = input<int, 6>();
    --ch, --cw, --dh, --dw;
    auto s = input<string>(h);
    Board brd(h, w);
    vector<vector<Pa>> adj(brd.area());
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (s[i][j] == '#') continue;
            for (auto [ni, nj] : brd.next(i, j)) {
                if (s[ni][nj] == '.') {
                    adj[brd.index(i, j)].push_back({0, brd.index(ni, nj)});
                }
            }
            for (int ni = i - 2; ni < i + 3; ++ni) {
                for (int nj = j - 2; nj < j + 3; ++nj) {
                    if (brd.contain(ni, nj) && s[ni][nj] == '.') {
                        adj[brd.index(i, j)].push_back({1, brd.index(ni, nj)});
                    }
                }
            }
        }
    }
    ZeroOneBFS bfs(adj);
    Vec cost = bfs.search(brd.index(ch, cw));
    int ans = cost[brd.index(dh, dw)];
    if (ans == INF) ans = -1;
    print(ans);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
