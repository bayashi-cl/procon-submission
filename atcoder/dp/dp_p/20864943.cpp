#pragma region template
// clang-format off
// #include <bits/stdc++.h>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

using ll = long long;

const int INF = INT_MAX / 2;
const ll LINF = LLONG_MAX / 2;
const int MOD = 1e9 + 7;

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
template<class T>void printvec(vector<T>& v) { for (T i : v) cout << i << " "; cout << endl;}

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11); }; } pre_exec_t;
// clang-format on
#pragma endregion

struct DFS {
    vector<vector<int>> graph;
    vector<int> last_order;
    DFS(vector<vector<int>> graph, int start) : graph(graph) { search(start); }

   private:
    void search(int now, int from = -1) {
        for (int to : graph[now]) {
            if (to == from) continue;
            search(to, now);
        }
        last_order.push_back(now);
    }
};

int main() {
    int N;
    cin >> N;
    vector<vector<int>> tree(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    vector<vector<ll>> dp(N, {1, 0});
    DFS d(tree, 0);
    for (auto&& i : d.last_order) {
        dp[i] = {1, 1};
        for (auto&& j : tree[i]) {
            dp[i][0] *= (dp[j][0] + dp[j][1]) % MOD;
            dp[i][0] %= MOD;
            dp[i][1] *= dp[j][0];
            dp[i][1] %= MOD;
        }
    }
    cout << (dp[0][0] + dp[0][1]) % MOD << endl;
    return 0;
}
