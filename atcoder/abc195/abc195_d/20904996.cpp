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

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<pair<int, int>> baggage(N);
    for (int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        baggage[i] = make_pair(v, w);
    }
    sort(baggage.begin(), baggage.end());
    reverse(baggage.begin(), baggage.end());
    vector<int> box(M);
    for (auto&& i : box) cin >> i;
    for (int q = 0; q < Q; q++) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        vector<int> copy_box(box);
        for (int i = l; i <= r; i++) {
            copy_box.erase(copy_box.begin() + l - 1);
        }
        sort(copy_box.begin(), copy_box.end());
        for (auto&& i : baggage) {
            auto&& itr =
                lower_bound(copy_box.begin(), copy_box.end(), i.second);
            if (itr == copy_box.end()) continue;
            ans += i.first;
            copy_box.erase(itr);
        }
        cout << ans << endl;
    }

    return 0;
}
