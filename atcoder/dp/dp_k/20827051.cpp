#pragma region template
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

struct pre_exec {
    pre_exec() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} pre_exec_t;
#pragma endregion

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for (auto&& i : a) cin >> i;
    vector<bool> dp(K + 1);
    for (int i : irange(K + 1)) {
        bool b = true;
        for (int j : a) {
            if (i - j >= 0) {
                b &= dp[i - j];
            }
            dp[i] = !b;
        }
    }
    if (dp[K]) {
        cout << "First" << endl;
    } else {
        cout << "Second" << endl;
    }
    return 0;
}
