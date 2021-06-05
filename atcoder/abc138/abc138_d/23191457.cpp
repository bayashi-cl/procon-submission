#pragma region include
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
// #include <queue>
// #include <set>
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

struct DepthFirstSearch {
    vector<vector<int>> graph;
    vector<int> add;
    // vector<int> first_order;
    // vector<int> last_order;
    vector<int> count;
    DepthFirstSearch(vector<vector<int>> graph, int start, vector<int> add)
        : graph(graph), add(add) {
        count.resize(graph.size());
        search(start);
    }
    void search(int now, int from = -1, int cnt = 0) {
        // first_order.push_back(now);
        count[now] = cnt + add[now];
        for (int to : graph[now]) {
            if (to == from) continue;
            search(to, now, count[now]);
        }
        // last_order.push_back(now);
    }
};

void main() {
    int n, q;
    cin >> n >> q;
    VecVec<int> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    vector<int> add(n);
    for (int i = 0; i < q; i++) {
        int p, x;
        cin >> p >> x;
        add[p - 1] += x;
    }
    auto dsu = DepthFirstSearch(adj, 0, add);
    cout << dsu.count << endl;
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    return 0;
}
