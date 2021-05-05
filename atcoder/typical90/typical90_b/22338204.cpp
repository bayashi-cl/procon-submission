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

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

using ll = long long;

const int INF = INT_MAX / 2;
const ll LINF = LLONG_MAX / 2;
const int MOD = 1e9 + 7;
const int ASCII_0 = 48;

template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
template<class T>void printvec(const vector<T>& v) { for (T i : v) cout << i << " "; cout << endl;}

struct pre_exec {pre_exec() {cin.tie(nullptr); ios::sync_with_stdio(false); cout << fixed << setprecision(11) << boolalpha; }; } pre_exec_t;
// clang-format on
#pragma endregion

bool ac(string can) {
    int j = 0;
    for (char s : can) {
        if (s == '(') {
            j++;
        } else {
            j--;
        }
        if (j < 0) return false;
    }
    if (j == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int n;
    cin >> n;
    for (ll i : irange(1 << n)) {
        string can = "";
        for (int j = n - 1; j >= 0; j--) {
            if ((i & (1 << j)) == 0) {
                can += "(";
            } else {
                can += ")";
            }
        }
        if (ac(can)) cout << can << endl;
    }

    return 0;
}
