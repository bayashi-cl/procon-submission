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
#include <vector>
#pragma endregion

namespace mine {
#pragma region template
// clang-format off
using std::cin, std::cout, std::endl, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
template <class T> using Vec = std::vector<T>;
template <class T> using VecVec = std::vector<std::vector<T>>;
template <class T> bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> void printvec(const Vec<T>& v) {for (T i : v) cout << i << " "; cout << endl;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
constexpr int MOD = 1e9 + 7;
// clang-format on
#pragma endregion

void main() {
    string s, t;
    cin >> s >> t;
    int min_cnt = INF;

    int lens = s.size();
    int lent = t.size();
    for (int i : irange(lens - lent + 1)) {
        string substr = s.substr(i, lent);
        int cnt = 0;
        for (int j : irange(lent)) {
            if (t[j] != substr[j]) cnt++;
        }
        chmin(min_cnt, cnt);
    }
    cout << min_cnt << endl;
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    return 0;
}
