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

vector<int> bfs(VecVec& adj, int start) {
    int n_node = adj.size();
    Vec cost(n_node, INF);
    cost[start] = 0;
    std::queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int top = que.front();
        que.pop();
        for (auto&& to : adj[top]) {
            if (cost[to] != INF) continue;
            cost[to] = cost[top] + 1;
            que.push(to);
        }
    }
    return cost;
}
void solve() {
    int h, w, n;
    cin >> h >> w >> n;
    auto idx = [&](int i, int j) { return w * i + j; };
    auto board = input<string>(h);

    vector<Pa> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<Pa> factory(n + 1);
    VecVec graph(h * w);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (board[i][j] == 'X') continue;
            if (board[i][j] == 'S') {
                factory[0] = {i, j};
            } else if (board[i][j] != '.') {
                int hard = board[i][j] - '0';
                factory[hard] = {i, j};
            }
            for (auto [di, dj] : delta) {
                int ni = i + di;
                int nj = j + dj;
                if (ni < 0 || h <= ni) continue;
                if (nj < 0 || w <= nj) continue;
                if (board[ni][nj] == 'X') continue;

                graph[idx(i, j)].push_back(idx(ni, nj));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int from = idx(factory[i].first, factory[i].second);
        int to = idx(factory[i + 1].first, factory[i + 1].second);
        ans += bfs(graph, from)[to];
    }
    print(ans);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
