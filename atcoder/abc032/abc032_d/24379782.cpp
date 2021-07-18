#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <valarray>
#include <vector>

namespace bys {
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
inline std::istream& operator>>(std::istream& is, mint& m) {ll n; is >> n; m = n; return is;}
inline std::ostream& operator<<(std::ostream& os, const mint& m) { os << m.val(); return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class T> inline T input() {T n; cin >> n; return n;}
template <class T> inline vector<T> input(int n) {vector<T> res(n); for (auto&& r : res) cin >> r; return res;}
template <class T, size_t N> inline std::array<T, N> input() {std::array<T, N> res; for (auto&& r : res) cin >> r; return res;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
}  // namespace bys

namespace bys {
void solve() {
    auto [n, w] = input<int, 2>();
    ll max_v = 0, max_w = 0;
    vector<pair<ll, ll>> wv;
    for (int i = 0; i < n; i++) {
        auto [vi, wi] = input<ll, 2>();
        chmax(max_v, vi);
        chmax(max_w, wi);
        wv.push_back({wi, vi});
    }
    if (n <= 30) {
        vector<pair<ll, ll>> wv_left, wv_right, ks_left, ks_right;
        for (int i = 0; i < n / 2; i++) wv_left.push_back(wv[i]);
        for (int i = n / 2; i < n; i++) wv_right.push_back(wv[i]);
        int n_left = wv_left.size();
        int n_right = wv_right.size();

        for (int s = 0; s < (1 << n_left); s++) {
            ll weight = 0, value = 0;
            for (int b = 0; b < n_left; b++) {
                if ((s & (1 << b)) == 0) continue;
                weight += wv_left[b].first;
                value += wv_left[b].second;
            }
            if (weight <= w) ks_left.push_back({weight, value});
        }

        for (int s = 0; s < (1 << n_right); s++) {
            ll weight = 0, value = 0;
            for (int b = 0; b < n_right; b++) {
                if ((s & (1 << b)) == 0) continue;
                weight += wv_right[b].first;
                value += wv_right[b].second;
            }
            if (weight <= w) ks_right.push_back({weight, value});
        }
        sort(std::begin(ks_right), std::end(ks_right));
        for (int i = 0; i < (int)ks_right.size() - 1; i++) {
            chmax(ks_right[i + 1].second, ks_right[i].second);
        }

        ll ans = 0;
        for (auto [weight, value] : ks_left) {
            ll re = w - weight;
            pair<ll, ll> th = {re, LINF};
            auto itr =
                std::upper_bound(std::begin(ks_right), std::end(ks_right), th);
            itr--;
            chmax(ans, value + (*itr).second);
        }
        print(ans);
    } else if (max_w <= 1000) {
        vector<vector<ll>> dp(n + 1, vector<ll>(n * max_w + 1));
        for (int i = 1; i <= n; i++) {
            auto [wi, vi] = wv[i - 1];
            for (int j = 0; j <= n * max_w; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - wi >= 0) chmax(dp[i][j], dp[i - 1][j - wi] + vi);
            }
        }
        print(dp[n][w]);
    } else {
        vector<vector<ll>> dp(n + 1, vector<ll>(max_v * n + 1, LINF));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            auto [wi, vi] = wv[i - 1];
            for (int j = 0; j <= n * max_v; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - vi >= 0) chmin(dp[i][j], dp[i - 1][j - vi] + wi);
            }
        }
        for (int i = max_v * n; i >= 0; --i) {
            if (dp[n][i] <= w) {
                print(i);
                break;
            }
        }
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
