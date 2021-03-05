#include <bits/stdc++.h>
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

using ll = long long;
using P = pair<int, int>;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int dp(int i, vector<vector<int>>& graph, vector<int>& memo,
       vector<bool>& done) {
    if (done[i]) return memo[i];
    int ans = 0;
    for (auto&& to : graph[i]) {
        ans = max(ans, dp(to, graph, memo, done) + 1);
    }
    memo[i] = ans;
    done[i] = true;
    return ans;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N, vector<int>());
    vector<int> memo(N);
    vector<bool> done(N);
    for (auto&& i : irange(M)) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
    }
    int ans = 0;
    for (auto&& i : irange(N)) {
        ans = max(ans, dp(i, graph, memo, done));
    }
    cout << ans << endl;
    return 0;
}
