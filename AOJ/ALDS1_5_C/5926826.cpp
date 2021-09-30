#include <cassert>
#include <cmath>
#include <complex>
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
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
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
namespace geo {
const double EPS = 1e-9;
const double PI = std::acos(-1.0);
int sgn(const double a) { return (a < -EPS ? -1 : (a > EPS ? +1 : 0)); }

using Point = std::complex<double>;
double len(Point a) { return std::abs(a); }
double dot(Point a, Point b) { return (a * std::conj(b)).real(); }
double det(Point a, Point b) { return (a * std::conj(b)).imag(); }
Point rot(Point a, double theta) {
    Point r(std::cos(theta), std::sin(theta));
    return a * r;
}
using Segment = pair<Point, Point>;
double len(Segment s) { return std::abs(s.second - s.first); }
bool cross(Segment a, Segment b) {
    double d1 = det(a.second - a.first, b.first - a.first);
    double d2 = det(a.second - a.first, b.second - a.first);
    double d3 = det(b.second - b.first, a.first - b.first);
    double d4 = det(b.second - b.first, a.second - b.first);
    return (sgn(d1) * sgn(d2) == -1 && sgn(d3) * sgn(d4) == -1);
}
}  // namespace geo
void koch(geo::Point p1, geo::Point p2, vector<geo::Point>& ans, int depth,
          int bottom) {
    if (depth == bottom) return;

    geo::Point s = (2.0 * p1 + p2) / 3.0;
    geo::Point t = (p1 + 2.0 * p2) / 3.0;
    geo::Point st = t - s;
    geo::Point st_rot = geo::rot(st, geo::PI / 3.0);
    geo::Point u = s + st_rot;

    koch(p1, s, ans, depth + 1, bottom);
    ans.push_back(s);
    koch(s, u, ans, depth + 1, bottom);
    ans.push_back(u);
    koch(u, t, ans, depth + 1, bottom);
    ans.push_back(t);
    koch(t, p2, ans, depth + 1, bottom);
}
void solve() {
    auto n = input<int>();
    vector<geo::Point> ans;
    ans.push_back({0, 0});
    koch({0, 0}, {100, 0}, ans, 0, n);
    ans.push_back({100, 0});
    for (auto&& p : ans) cout << p.real() << ' ' << p.imag() << endl;
}

}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}

