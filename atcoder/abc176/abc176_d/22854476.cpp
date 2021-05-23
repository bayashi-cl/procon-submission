#pragma region include
#include <atcoder/dsu>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
// #include <bits/stdc++.h>
// #include <cmath>
#include <iomanip>
#include <iostream>
// #include <iterator>
#include <limits>
// #include <map>
// #include <numeric>
#include <queue>
#include <set>
// #include <stack>
#include <string>
#include <valarray>
#include <vector>
#pragma endregion

namespace mine {
#pragma region template
// clang-format off
using std::cin, std::cout, std::clog, std::endl, std::vector, std::valarray, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
template <class T> using Vec = std::vector<T>;
template <class T> using VecVec = std::vector<std::vector<T>>;
template <class T> bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> void printvec(const Vec<T>& v) {for (T i : v) cout << i << " "; cout << endl;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
constexpr int MOD = 1e9 + 7;
// clang-format on
#pragma endregion

int bfs(Vec<std::set<int>>& graph, int start, int goal) {
    int n_node = graph.size();
    std::queue<int> que;
    que.push(start);
    Vec<int> cost(n_node, -1);
    cost[start] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : graph[v]) {
            if (cost[to] != -1) continue;
            cost[to] = cost[v] + 1;
            que.push(to);
        }
    }
    return cost[goal];
}

int h, w;

int index(int i, int j) { return i * w + j; }

void main() {
    cin >> h >> w;
    int ch, cw, dh, dw;
    cin >> ch >> cw >> dh >> dw;
    VecVec<bool> maze(h, Vec<bool>(w));
    for (auto&& i : irange(h)) {
        for (auto&& j : irange(w)) {
            char s;
            cin >> s;
            if (s == '.') {
                maze[i][j] = true;
            }
        }
    }
    atcoder::dsu uft(h * w);

    vector<std::pair<int, int>> delta = {
        std::make_pair(1, 0),
        std::make_pair(-1, 0),
        std::make_pair(0, 1),
        std::make_pair(0, -1),
    };

    for (int i : irange(h)) {
        for (auto&& j : irange(w)) {
            if (!maze.at(i).at(j)) continue;
            int here = index(i, j);
            for (auto&& d : delta) {
                try {
                    if (maze.at(i + d.first).at(j + d.second)) {
                        uft.merge(here, index(i + d.first, j + d.second));
                    }
                } catch (...) {
                }
            }
        }
    }
    Vec<std::set<int>> adj(h * w);
    for (int i : irange(h)) {
        for (auto&& j : irange(w)) {
            if (!maze[i][j]) continue;
            int here = index(i, j);
            for (int k = i - 2; k <= i + 2; k++) {
                for (int l = j - 2; l <= j + 2; l++) {
                    try {
                        int to = index(k, l);
                        if (maze.at(k).at(l) && (!uft.same(here, to))) {
                            int l_here = uft.leader(here);
                            int l_to = uft.leader(to);
                            adj[l_here].insert(l_to);
                            adj[l_to].insert(l_here);
                        }
                    } catch (...) {
                    }
                }
            }
        }
    }

    int start = uft.leader((ch - 1) * w + (cw - 1));
    int goal = uft.leader((dh - 1) * w + (dw - 1));
    int ans = bfs(adj, start, goal);
    cout << ans << endl;
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    return 0;
}
