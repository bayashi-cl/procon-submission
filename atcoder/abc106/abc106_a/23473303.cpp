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
#include <valarray>
#include <vector>
#pragma endregion

namespace mine {
#pragma region template
// clang-format off
using std::cin, std::cout, std::endl, std::vector, std::string, boost::irange;
using ll = long long int;
using mint = atcoder::modint1000000007;
template <class T = int> using Vec = std::vector<T>;
template <class T = int> using VecVec = std::vector<std::vector<T>>;
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class Tail> void print(Tail&& tail) {cout << tail << endl;}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
inline void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
constexpr int MOD = 1e9 + 7;
// clang-format on
#pragma endregion

void main() {
    int a, b;
    cin >> a >> b;
    print((a - 1) * (b - 1));
}

}  // namespace mine

int main() {
    mine::init();
    mine::main();
    return 0;
}
