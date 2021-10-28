#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
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
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace bys {
// clang-format off
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;
using ll = long long int;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T> using uset = std::unordered_set<T>;
template <class S, class T> using umap = std::unordered_map<S, T>;
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
template <class T, class U> std::istream& operator>>(std::istream& is, std::pair<T, U>& p) { return is >> p.first >> p.second; }
template <typename T, typename U> std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) { return os << p.first << " " << p.second; }
struct is_container_impl { template <typename T> static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{}); template <typename T> static auto check(...) -> std::false_type; };
template <typename T> class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept { std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; }); return os << *std::prev(std::end(container)); }
template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value && !std::is_same<C, std::wstring>::value, std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) { std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; }); return is; }
template <class T> inline T input() { T n; cin >> n; return n; }
template <class T> inline vector<T> input(int n) { vector<T> res(n); cin >> res; return res; }
template <class T, size_t N> inline std::array<T, N> input() { std::array<T, N> res; cin >> res; return res; }
template <class S, class T, class... Us> std::tuple<S, T, Us...> input() { std::tuple<S, T, Us...> res; std::apply([](auto&... e) { (cin >> ... >> e); }, res); return res; }
struct Print {
    std::ostream& os;
    char sep = ' ', end = '\n';
    Print(std::ostream& os = std::cout) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T> void operator()(const T& a) { os << a << end; }
    template <class T, class... Ts> void operator()(const T& a, const Ts&... b) { os << a; (os << ... << (os << sep, b)); os << end; }
} print, debug(std::cerr);
template <class T> inline bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
template <class T> inline bool chmin(T& a, const T& b) { if (b < a) { a = b; return 1; } return 0; }
template <class T> inline T ceil(T a, T b) { return (a + b - 1) / b; }
inline bool pop(int s, int d) { return s & (1 << d); }
inline void init() { cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11); std::cerr << std::boolalpha; }
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
}  // namespace bys

namespace bys {
namespace geo {
const double EPS = 1e-9;
const double PI = std::acos(-1.0);
int sgn(double a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }
int sgn(int a) { return (a < 0) ? -1 : (a > 0) ? 1 : 0; }
bool isclose(double a, double b) { return sgn(a - b) == 0; }
bool isclose(int a, int b) { return sgn(a - b) == 0; }
double radian(double degree) { return degree * (PI / 180.0); }
double degree(double theta) { return theta * (180.0 / PI); }

// ベクトル・点
template <class T>
struct Vec2d {
    T x, y;
    Vec2d() : x(0.0), y(0.0) {}
    Vec2d(T x, T y) : x(x), y(y) {}
    // clang-format off
    friend std::istream& operator>>(std::istream& is, Vec2d<T>& v) { return is >> v.x >> v.y; }
    friend std::ostream& operator<<(std::ostream& os, const Vec2d<T>& v) { return os << v.x << ' ' << v.y; }
    Vec2d operator+() const { return *this; }
    Vec2d operator-() const { return Vec2d(-x, -y); }
    Vec2d operator+(const Vec2d& rh) const { return Vec2d(x + rh.x, y + rh.y); }
    Vec2d operator-(const Vec2d& rh) const { return Vec2d(x - rh.x, y - rh.y); }
    Vec2d operator*(const T rh) const { return Vec2d(x * rh, y * rh); }
    Vec2d operator/(const int rh) const { return Vec2d(x / rh, y / rh); }
    Vec2d operator/(const double rh) const { return Vec2d(x / rh, y / rh); }
    Vec2d operator+=(const Vec2d& rh) { x += rh.x; y += rh.y; return *this; }
    Vec2d operator-=(const Vec2d& rh) { x -= rh.x; y -= rh.y; return *this; }
    Vec2d operator*=(const T rh) { x *= rh; y *= rh; return *this; }
    Vec2d operator/=(const T rh) { x /= rh; y /= rh; return *this; }
    bool operator==(const Vec2d& rh) const { return isclose(x, rh.x) && isclose(y, rh.y); }
    bool operator!=(const Vec2d& rh) const { return !(*this == rh); }
    // clang-format on

    T norm2() const { return x * x + y * y; }
    double norm() const { return std::sqrt(norm2()); }
    Vec2d normalized() const { return Vec2d(x / norm(), y / norm()); }
    double angle() const { return std::atan2(y, x); }
    Vec2d rotate(double theta) {
        double ct = std::cos(theta), st = std::sin(theta);
        return Vec2d(x * ct - y * st, x * st + y * ct);
    }
    double dot(const Vec2d& rh) const { return x * rh.x + y * rh.y; }
    double det(const Vec2d& rh) const { return x * rh.y - y * rh.x; }
    Vec2d normal() const { return Vec2d(-normalized().y, normalized().x); }
    Vec2d projection(const Vec2d& to) const {
        return to * (dot(to) / to.norm2());
    }
};

/*
+1: ab->bcが左に曲がる
-1: ab->bcが右に曲がる
+2: abcで直線上
-2: bacで直線上
 0: acbで直線上
 */
template <class T>
int iSP(const Vec2d<T>& a, const Vec2d<T>& b, const Vec2d<T>& c) {
    int flg = sgn((b - a).det(c - a));
    if (flg == 1) {
        return +1;
    } else if (flg == -1) {
        return -1;
    } else {
        if (sgn((b - a).dot(c - b)) > 0) {
            return +2;
        } else if (sgn((a - b).dot(c - a)) > 0) {
            return -2;
        } else {
            return 0;
        }
    }
}

// 直線・線分
template <class T>
struct Line {
    Vec2d<T> p, q;
    Line(Vec2d<T> p, Vec2d<T> q) : p(p), q(q) {}
    Vec2d<T> to_Vec2d() const { return q - p; }
    Vec2d<double> to_unit_Vec2d() const { return to_Vec2d().normalized(); }
    double slope() const { return to_Vec2d().angle(); }
    bool operator==(const Line& rh) const {
        return abs(iSP(p, q, rh.p)) != 1 && abs(iSP(p, q, rh.q)) != 1;
    }
    bool operator!=(const Line& rh) const { return !(*this == rh); }
};
template <class T>
struct Segment : Line<T> {
    Segment(Vec2d<T>& p, Vec2d<T>& q) : Line<T>::Line(p, q) {}
    double length() const { return this->to_Vec2d().norm(); }
    Vec2d<double> internal_division(double m, double n) const {
        return (this->r * n + this->s * m) / (m + n);
    }
    bool operator==(const Segment& rh) const {
        return (this->p == rh.p && this->q == rh.q) ||
               (this->p == rh.q && this->q == rh.p);
    }
    bool operator!=(const Segment& rh) const { return !(*this == rh); }
};
template <class T>
int iSP(const Segment<T>& s, const Vec2d<T>& c) {
    return iSP(s.p, s.q, c);
}
template <class T>
int iSP(const Line<T>& l, const Vec2d<T>& c) {
    return iSP(l.p, l.q, c);
}
template <class T>
bool cross(Line<T>& a, Line<T>& b) {
    return sgn(a.to_Vec2d().det(b.to_Vec2d())) != 0;
}
template <class T>
bool cross(Segment<T>& a, Segment<T>& b) {
    return iSP(a, b.p) * iSP(a, b.q) <= 0 && iSP(b, a.p) * iSP(b, a.q) <= 0;
}

// 多角形
template <class T>
struct Polygon {
    std::vector<Vec2d<T>> vertex;
    Polygon(std::initializer_list<Vec2d<T>> init)
        : vertex(init.begin(), init.end()) {}
    Polygon(std::vector<Vec2d<T>> vertex) : vertex(vertex) {}
    double area() const {
        int n_vertex = vertex.size();
        if (n_vertex < 3) return 0;
        double s = 0.0;
        for (int i = 0; i < n_vertex; ++i) {
            s += vertex[i].det(vertex[(i + 1) % n_vertex]);
        }
        return s * 0.5;
    };
};
}  // namespace geo
}  // namespace bys

namespace bys {
void solve() {
    auto [p1, p2] = input<geo::Vec2d<double>, 2>();
    p2 -= p1;
    auto q = input<int>();
    for (int i = 0; i < q; ++i) {
        auto p = input<geo::Vec2d<double>>();
        p -= p1;
        print(p.projection(p2) + p1);
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    return 0;
}

