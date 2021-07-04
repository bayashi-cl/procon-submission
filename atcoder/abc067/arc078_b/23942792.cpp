#pragma region template
#include <atcoder/dsu>
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

struct BreadthFirstSearch {
    vector<vector<int>> graph;
    int n_node;
    vector<int> prev;

    BreadthFirstSearch(vector<vector<int>> graph)
        : graph(graph), n_node(graph.size()) {}

    vector<int> search(int start) {
        vector<int> cost(n_node, INF);
        cost[start] = 0;
        prev.resize(n_node, -1);
        std::queue<int> que;
        que.push(start);

        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (int to : graph[from]) {
                if (cost[to] == INF) {
                    cost[to] = cost[from] + 1;
                    que.push(to);
                    prev[to] = from;
                }
            }
        }
        return cost;
    }

    vector<int> path_finder(int to) {
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
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int ai, bi;
        cin >> ai >> bi;
        adj[ai - 1].push_back(bi - 1);
        adj[bi - 1].push_back(ai - 1);
    }
    BreadthFirstSearch bfs(adj);
    bfs.search(0);
    auto path = bfs.path_finder(n - 1);
    int th = (path.size() + 1) / 2;
    Pa cut = {path[th], path[th - 1]};

    atcoder::dsu uft(n);
    for (auto&& f : irange(n)) {
        for (auto&& t : adj[f]) {
            if (f == cut.first && t == cut.second) continue;
            if (t == cut.first && f == cut.second) continue;

            uft.merge(f, t);
        }
    }

    if (uft.size(0) > uft.size(n - 1)) {
        print("Fennec");
    } else {
        print("Snuke");
    }
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    std::cout << std::flush;
    return 0;
}
