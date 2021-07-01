#pragma region template
#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
// #include <bits/stdc++.h>
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

namespace mine {
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
#pragma endregion

struct WarshallFloyd {
    using Edge = std::pair<ll, int>;
    using Adj = vector<vector<Edge>>;

    int n_node;
    vector<vector<ll>> cost;
    vector<int> prev;
    WarshallFloyd(const Adj& graph) {
        n_node = graph.size();
        cost.resize(n_node, vector<ll>(n_node, LINF));
        prev.resize(n_node, -1);

        for (int i = 0; i < n_node; i++) {
            for (auto [dist, j] : graph[i]) cost[i][j] = dist;
        }
    }

    void search() {
        for (int k = 0; k < n_node; k++) {
            for (int i = 0; i < n_node; i++) {
                for (int j = 0; j < n_node; j++) {
                    if (chmin(cost[i][j], cost[i][k] + cost[k][j])) prev[j] = k;
                }
            }
        }
    }

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
};

void main() {
    int n, m, r;
    cin >> n >> m >> r;
    Vec visit(r);
    cin >> visit;
    sort(std::begin(visit), std::end(visit));
    WarshallFloyd::Adj adj(n, vector<WarshallFloyd::Edge>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    WarshallFloyd wf(adj);
    wf.search();

    ll ans = LINF;
    do {
        ll d = 0;
        for (int i = 0; i < r - 1; i++) {
            d += wf.cost[visit[i] - 1][visit[i + 1] - 1];
        }
        chmin(ans, d);
    } while (std::next_permutation(std::begin(visit), std::end(visit)));

    print(ans);
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    std::cout << std::flush;
    return 0;
}
