#line 2 "byslib/template/bys.hpp"
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
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;

// alias
using ll = long long int;
using ld = long double;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;

// const
constexpr int MOD = 998244353;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;

// I/O
// pair
template <class T, class U>
std::istream& operator>>(std::istream& is, std::pair<T, U>& p) {
    return is >> p.first >> p.second;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << p.first << " " << p.second;
}

// STL container
struct is_container_impl {
    template <typename T>
    static auto check(T&& obj)
        -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container
    : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    std::for_each(std::begin(container), std::prev(std::end(container)),
                  [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container),
                  [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}

struct Print {
    std::ostream& os;
    char sep = ' ', end = '\n';
    Print() : os(std::cout) {}
    Print(std::ostream& os) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T>
    void operator()(const T& a) {
        os << a << end;
    }
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
} print, debug(std::cerr);

// utility
template <class T>
inline bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline bool chmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline T iceil(T a, T b) {
    return (a + b - 1) / b;
}
inline bool pop(int s, int d) { return s & (1 << d); }

// config
inline void init() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

// macro
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
#define EXIT(...)           \
    {                       \
        print(__VA_ARGS__); \
        return;             \
    }
}  // namespace bys
#line 2 "abc225_e/main.cpp"
namespace bys {
namespace geo {
const ld EPS = 1e-9;
const ld PI = std::acos(-1.0);
int sgn(ld a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }
bool isclose(ld a, ld b) { return sgn(a - b) == 0; }
ld radian(ld degree) { return degree * (PI / 180.0); }
ld degree(ld theta) { return theta * (180.0 / PI); }
// ベクトル・点
template <class T>
struct Point {
    T x, y;
    Point() : x(0.0), y(0.0) {}
    Point(T x, T y) : x(x), y(y) {}
    // clang-format off
    friend std::istream& operator>>(std::istream& is, Point& v) { return is >> v.x >> v.y; }
    friend std::ostream& operator<<(std::ostream& os, const Point& v) { return os << v.x << ' ' << v.y; }
    Point operator+() const { return *this; }
    Point operator-() const { return Point(-x, -y); }
    Point operator+(const Point& rh) const { return Point(x + rh.x, y + rh.y); }
    Point operator-(const Point& rh) const { return Point(x - rh.x, y - rh.y); }
    Point operator*(const T rh) const { return Point(x * rh, y * rh); }
    Point operator/(const T rh) const { return Point(x / rh, y / rh); }
    Point operator+=(const Point& rh) { x += rh.x; y += rh.y; return *this; }
    Point operator-=(const Point& rh) { x -= rh.x; y -= rh.y; return *this; }
    Point operator*=(const T rh) { x *= rh; y *= rh; return *this; }
    Point operator/=(const T rh) { x /= rh; y /= rh; return *this; }
    bool operator==(const Point& rh) const { return isclose(x, rh.x) && isclose(y, rh.y); }
    bool operator!=(const Point& rh) const { return !(*this == rh); }
    // clang-format on

    T norm2() const { return x * x + y * y; }
    ld norm() const { return std::sqrt(norm2()); }
    Point normalized() const { return Point(x / norm(), y / norm()); }
    ld angle() const { return std::atan2(y, x); }
    Point rotate(ld theta) {
        ld ct = std::cos(theta), st = std::sin(theta);
        return Point(x * ct - y * st, x * st + y * ct);
    }
    T dot(const Point& rh) const { return x * rh.x + y * rh.y; }
    T det(const Point& rh) const { return x * rh.y - y * rh.x; }
    Point normal() const { return Point(-normalized().y, normalized().x); }
    Point projection(const Point& to) const {
        return to * (dot(to) / to.norm2());
    }
    int quadrant() const {
        if (sgn(y) >= 0) return sgn(x) >= 0 ? 1 : 2;
        return sgn(x) >= 0 ? 4 : 3;
    }
    bool operator<(const Point& rh) const {
        int q = quadrant(), rhq = rh.quadrant();
        if (q != rhq) return q < rhq;
        return sgn(det(rh)) > 0;
    }
    bool operator<=(const Point& rh) const {
        int q = quadrant(), rhq = rh.quadrant();
        if (q != rhq) return q < rhq;
        return sgn(det(rh)) >= 0;
    }
};

/**
 * +1: ab->bcが左に曲がる
 * -1: ab->bcが右に曲がる
 * +2: abcで直線上
 * -2: bacで直線上
 *  0: acbで直線上
 */
template <class T>
int iSP(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
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
    Point<T> p, q;
    Line(Point<T> p, Point<T> q) : p(p), q(q) {}
    Point<T> to_Point() const { return q - p; }
    Point<ld> to_unit_Point() const { return to_Point().normalized(); }
    ld slope() const { return to_Point().angle(); }
    bool operator==(const Line& rh) const {
        return abs(iSP(p, q, rh.p)) != 1 && abs(iSP(p, q, rh.q)) != 1;
    }
    bool operator!=(const Line& rh) const { return !(*this == rh); }
};
template <class T>
struct Segment : Line<T> {
    Segment(Point<T>& p, Point<T>& q) : Line<T>::Line(p, q) {}
    ld length() const { return this->to_Point().norm(); }
    Point<ld> internal_division(ld m, ld n) const {
        return (this->p * n + this->q * m) / (m + n);
    }
    bool operator==(const Segment& rh) const {
        return (this->p == rh.p && this->q == rh.q) ||
               (this->p == rh.q && this->q == rh.p);
    }
    bool operator!=(const Segment& rh) const { return !(*this == rh); }
};
template <class T>
int iSP(const Point<T>& p, const Line<T>& l) {
    return iSP(l.p, l.q, p);
}

template <class T>
bool is_parallel(const Line<T>& a, const Line<T>& b) {
    return sgn(a.to_Point().det(b.to_Point())) == 0;
}
template <class T>
bool is_vertial(const Line<T>& a, const Line<T>& b) {
    return sgn(a.to_Point().dot(b.to_Point())) == 0;
}
template <class T>
bool is_cross(const Line<T>& a, const Line<T>& b) {
    return sgn(a.to_Point().det(b.to_Point())) != 0 ||
           sgn(a.to_Point().det(b.p - a.p)) == 0;
}
template <class T>
bool is_cross(const Segment<T>& a, const Segment<T>& b) {
    return iSP(b.p, a) * iSP(b.q, a) <= 0 && iSP(a.p, b) * iSP(a.q, b) <= 0;
}
template <class T>
ld angle(const Line<T>& a, const Line<T>& b) {
    return std::atan2(a.to_Point().det(b.to_Point()),
                      a.to_Point().dot(b.to_Point()));
}
/**
 * ∠abcが
 * -1: 鈍角
 *  0: 直角
 * +1: 鋭角
 */
template <class T>
int angle_type(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return sgn((a - b).dot(c - b));
}
template <class T>
ld distance(const Point<T>& p, const Line<T>& l) {
    return abs(l.to_Point().det(p - l.p) / (l.q - l.p).norm());
}
template <class T>
ld distance(const Point<T>& p, const Segment<T>& s) {
    if (angle_type(s.p, s.q, p) == -1) {
        return (p - s.q).norm();
    } else if (angle_type(s.q, s.p, p) == -1) {
        return (p - s.p).norm();
    } else {
        return distance(p, Line(s.p, s.q));
    }
}
template <class T>
ld distance(const Segment<T>& s, const Segment<T>& t) {
    if (is_cross(s, t)) return 0;

    return min({distance(s.p, t), distance(s.q, t), distance(t.p, s),
                distance(t.q, s)});
}
template <class T>
std::pair<bool, Point<T>> cross_point(const Line<T>& a, const Line<T>& b) {
    if (!is_cross(a, b)) return {false, Point<T>()};
    Point s = b.p - a.p;
    Point res = b.p + b.to_Point() * abs(a.to_Point().det(s) /
                                         a.to_Point().det(b.to_Point()));
    return {true, res};
}
template <class T>
Point<T> projection(const Point<T>& p, const Line<T>& l) {
    return (p - l.p).projection(l.to_Point()) + l.p;
}
template <class T>
Point<T> reflection(const Point<T>& p, const Line<T>& l) {
    return p + (projection(p, l) - p) * 2;
}

// 多角形
template <class T>
struct Polygon {
    int n_vertex;
    std::vector<Point<T>> vertex;
    Polygon(std::initializer_list<Point<T>> init)
        : n_vertex(init.size()), vertex(init.begin(), init.end()) {}
    Polygon(std::vector<Point<T>> vertex)
        : n_vertex(vertex.size()), vertex(vertex) {}
    T area2() const {
        if (n_vertex < 3) return 0;
        ld s = 0.0;
        for (int i = 0; i < n_vertex; ++i) {
            s += vertex[i].det(vertex[(i + 1) % n_vertex]);
        }
        return s * 0.5;
    };
    ld area() const { return area2() * 0.5; }
    bool is_convex() const {
        int left = 0;
        int right = 0;
        for (int i = 0; i < n_vertex; ++i) {
            int res = iSP(vertex[i], vertex[(i + 1) % n_vertex],
                          vertex[(i + 2) % n_vertex]);
            if (res == -1) left++;
            if (res == 1) right++;
        }
        return left == 0 || right == 0;
    }
};
}  // namespace geo
}  // namespace bys

namespace bys {
void solve() {
    auto n = input<int>();
    vector<pair<geo::Point<ll>, geo::Point<ll>>> hu(n);
    for (int i = 0; i < n; ++i) {
        auto [x, y] = input<ll, 2>();
        hu[i] = {{x - 1, y}, {x, y - 1}};
    }
    sort(std::begin(hu), std::end(hu));
    int ans = 0;
    geo::Point<ll> now(1, 0);
    for (auto& [end, start] : hu) {
        if (now <= start) {
            ans++;
            now = end;
        }
    }
    print(ans);
    // vector<pair<ld, ld>> hu(n);
    // for (int i = 0; i < n; ++i) {
    //     auto [x, y] = input<int, 2>();
    //     hu[i] = {geo::Point(x - 1, y).angle(), geo::Point(x, y - 1).angle()};
    // }
    // sort(std::begin(hu), std::end(hu));
    // int ans = 0;
    // ld now = -1;
    // for (int i = 0; i < n; ++i) {
    //     auto [end, start] = hu[i];
    //     if (now <= start) {
    //         ans++;
    //         now = end;
    //     }
    // }
    // print(ans);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    return 0;
}
