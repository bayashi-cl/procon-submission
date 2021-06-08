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

void main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    cin >> s;

    atcoder::dsu col(h * w);
    atcoder::dsu row(h * w);

    for (auto&& i : irange(h)) {
        for (auto&& j : irange(w)) {
            if (s[i][j] == '#') continue;
            int here = i * w + j;
            if (i != 0) {
                if (s[i - 1][j] == '.') col.merge(here, here - w);
            }
            if (i != h - 1) {
                if (s[i + 1][j] == '.') col.merge(here, here + w);
            }
            if (j != 0) {
                if (s[i][j - 1] == '.') row.merge(here, here - 1);
            }
            if (j != w - 1) {
                if (s[i][j + 1] == '.') row.merge(here, here + 1);
            }
        }
    }

    int ans = -1;
    for (auto&& i : irange(h)) {
        for (auto&& j : irange(w)) {
            if (s[i][j] == '#') continue;
            int here = i * w + j;
            int area = col.size(here) + row.size(here) - 1;
            chmax(ans, area);
        }
    }
    cout << ans << endl;
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    return 0;
}
