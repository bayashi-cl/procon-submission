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
#include <vector>
#pragma endregion

namespace mine {
#pragma region template
// clang-format off
using std::cin, std::cout, std::clog, std::endl, std::vector, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
template <class T> using Vec = std::vector<T>;
template <class T> using VecVec = std::vector<std::vector<T>>;
template <class T> bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> void printvec(const Vec<T>& v) {for (T i : v) cout << i << " "; cout << endl;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
constexpr int MOD = 1e9 + 7;
// clang-format on
#pragma endregion

void main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n), c(n);
    cin >> p >> c;
    for (auto&& pi : p) pi--;

    ll ans = -LINF;
    for (auto&& i : irange(n)) {
        int now = i;
        ll cycle_score = 0;
        int loop = 0;

        while (true) {
            loop++;
            cycle_score += c[now];
            now = p[now];
            if (now == i) break;
        }

        ll path = 0;
        int cnt = 0;

        while (true) {
            cnt++;
            path += c[now];

            if (cnt > k) break;

            int num = (k - cnt) / loop;
            ll score = path + std::max(0LL, cycle_score) * num;
            chmax(ans, score);

            now = p[now];
            if (now == i) break;
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
