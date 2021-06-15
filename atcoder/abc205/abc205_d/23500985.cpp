#pragma region template
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

namespace mine {
using std::cin, std::cout, std::endl, std::vector, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
using Vec = std::vector<int>;
using VecVec = std::vector<std::vector<int>>;
using Pa = std::pair<int, int>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
#pragma endregion

template <typename T, class Lambda, class... Args>
T meguru_bisect(T ok, T ng, Lambda check, Args... args) {
    while (std::abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        if (check(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

void main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;
    std::sort(std::begin(a), std::end(a));
    ll ok = 2e18;
    ll ng = 0;

    auto check = [&a](ll mid, ll k) {
        ll inc = std::upper_bound(a.begin(), a.end(), mid) - a.begin();
        return mid - inc >= k;
    };

    for (int i = 0; i < q; i++) {
        ll k;
        cin >> k;
        ll ans = meguru_bisect(ok, ng, check, k);
        print(ans);
    }
}
}  // namespace mine

int main() {
    mine::init();
    mine::main();
    std::cout << std::flush;
    return 0;
}
