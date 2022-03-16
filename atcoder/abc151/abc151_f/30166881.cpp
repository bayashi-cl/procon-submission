#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
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
using Pall = pair<ll, ll>;
using ibool = std::int8_t;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;
}  // namespace bys

namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
#include <utility>

namespace bys {
template <class, class = void>
struct has_lshift_to_ostream : std::false_type {};
template <class T>
struct has_lshift_to_ostream<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T&>())>> : std::true_type {};

template <class, class = void>
struct has_rshift_from_istream : std::false_type {};
template <class T>
struct has_rshift_from_istream<T, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>())>> : std::true_type {};

template <class T, class = void>
struct has_tuple_interface : std::false_type {};
template <class T>
struct has_tuple_interface<T, std::void_t<decltype(std::tuple_size<T>())>> : std::true_type {};

template <class, class = void>
struct has_iterator : std::false_type {};
template <class T>
struct has_iterator<T, std::void_t<typename T::iterator>> : std::true_type {};

struct Int1 {};
}  // namespace bys

namespace bys {
struct Printer {
    Printer(std::ostream& os_) : os(os_) {}
    ~Printer() { os << std::flush; }

    template <class T>
    void cat(T&& v) {
        if constexpr (has_lshift_to_ostream<std::decay_t<T>>::value) {
            os << v;
        } else if constexpr (has_iterator<std::decay_t<T>>::value) {
            string sep2;
            if constexpr (has_iterator<std::decay_t<typename std::decay_t<T>::value_type>>::value) {
                sep2 = _end;
            } else {
                sep2 = _sep;
            }
            for (auto &&itr = std::begin(v), end = std::end(v); itr != end; ++itr) {
                cat(*itr);
                if (std::next(itr) != end) cat(sep2);
            }
        } else if constexpr (has_tuple_interface<std::decay_t<T>>::value) {
            print_tuple(std::forward<T>(v), std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>());
        } else {
            static_assert([] { return false; }(), "type error");
        }
    }
    void print() { cat(_end); }
    template <class T>
    void print(T&& top) {
        cat(std::forward<T>(top));
        cat(_end);
    }
    template <class T, class... Ts>
    void print(T&& top, Ts&&... args) {
        cat(std::forward<T>(top));
        cat(_sep);
        print(std::forward<Ts>(args)...);
    }
    template <class... Ts>
    void operator()(Ts&&... args) {
        print(std::forward<Ts>(args)...);
    }

    void flush() { os << std::flush; }
    template <class... Ts>
    void send(Ts&&... args) {
        print(std::forward<Ts>(args)...);
        flush();
    }

    Printer set(string sep_ = " ", string end_ = "\n") {
        _sep = sep_;
        _end = end_;
        return *this;
    }
    void lf() { cat(_end); }

   private:
    std::ostream& os;
    std::string _sep = " ", _end = "\n";
    template <std::size_t I, class T>
    inline void print_tuple_element(T&& elem) {
        if constexpr (I != 0) cat(_sep);
        cat(std::forward<T>(elem));
    }
    template <class Tp, std::size_t... I>
    inline void print_tuple(Tp&& tp, std::index_sequence<I...>) {
        (print_tuple_element<I>(std::forward<decltype(std::get<I>(tp))>(std::get<I>(tp))), ...);
    }
};
}  // namespace bys

namespace bys {
struct Scanner {
    Scanner(std::istream& is_) : is(is_){};

    template <class... Ts>
    void scan(Ts&... args) {
        (is >> ... >> args);
    }

    template <class T, class... Us>
    decltype(auto) read() {
        if constexpr (sizeof...(Us) == 0) {
            if constexpr (has_rshift_from_istream<T>::value) {
                T res;
                is >> res;
                return res;
            } else if constexpr (has_tuple_interface<T>::value) {
                auto res = read_tuple<T>(std::make_index_sequence<std::tuple_size_v<T>>());
                return res;
            } else if constexpr (std::is_same_v<T, Int1>) {
                int res;
                is >> res;
                --res;
                return res;
            } else if constexpr (has_iterator<T>::value) {
                //! TODO: 一行読んでsplit
                static_assert([] { return false; }(), "NotImplementedError");
            } else {
                static_assert([] { return false; }(), "TypeError");
            }
        } else {
            return std::tuple{read<T>(), read<Us>()...};
        }
    }

    template <class T, std::size_t N, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    std::array<R, N> read() {
        std::array<R, N> res;
        for (auto&& e : res) e = read<T>();
        return res;
    }

    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<R> readvec(int n) {
        vector<R> res(n);
        for (auto&& e : res) e = read<T>();
        return res;
    }
    template <class T, typename R = std::conditional_t<std::is_same_v<T, Int1>, int, T>>
    vector<vector<R>> readvec(int n, int m) {
        vector<vector<R>> res(n);
        for (auto&& e : res) e = readvec<T>(m);
        return res;
    }

    template <class Lambda = std::function<int(std::string)>,
              typename T = std::invoke_result_t<std::decay_t<Lambda>, std::string>>
    std::vector<T> readln(
        Lambda f = [](string x) { return std::stoi(x); }, char sep = ' ') {
        std::ws(is);
        std::string elem;
        std::getline(is, elem);
        std::stringstream ss{elem};
        std::vector<T> res;
        while (std::getline(ss, elem, sep)) res.emplace_back(f(elem));
        return res;
    }
    std::string getline(bool skip_ws = true) {
        if (skip_ws) std::ws(is);
        std::string res;
        std::getline(is, res);
        return res;
    }

   private:
    std::istream& is;
    template <class Tp, std::size_t... I>
    inline decltype(auto) read_tuple(std::index_sequence<I...>) {
        return Tp{read<typename std::tuple_element_t<I, Tp>>()...};
    }
};
}  // namespace bys

namespace bys {
__attribute__((constructor)) void setup_io() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(11);
    std::cerr << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

Printer print(std::cout), debug(std::cerr);
Scanner scanner(std::cin);
}  // namespace bys
// clang-format off
/**
 * @brief マクロ
 */
#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...) { std::cerr << "[debug] line" << std::setw(4) << __LINE__ << ": "; debug(__VA_ARGS__); }
#else
#define DEBUG(...)
#endif
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
//! @brief [[maybe_unused]]な変数を生成。
#define UV [[maybe_unused]] auto CONCAT(unused_val_, __LINE__)
#define RE std::runtime_error("line: " + std::to_string(__LINE__) + ", func: " + __func__)
// clang-format on

namespace bys {
struct Solver {
    int IT = 1;
    Solver() {}
    void solve();
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys

namespace bys::geo {
const ld EPS = 1e-9;
const ld PI = std::acos(-1.0);
const ld TAU = PI * 2;
int sgn(ld a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }
bool isclose(ld a, ld b) { return sgn(a - b) == 0; }
ld radian(ld degree) { return degree * (PI / 180.0); }
ld degree(ld theta) { return theta * (180.0 / PI); }
}  // namespace bys::geo

namespace bys::geo {
//! @brief 点/ベクトル
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
    Point rotate(ld theta) const {
        ld ct = std::cos(theta), st = std::sin(theta);
        return Point(x * ct - y * st, x * st + y * ct);
    }
    Point rotate90() const { return Point(-y, x); }
    //! @brief マンハッタン距離用。45度回転して√2倍する
    Point manhattan_rotate() const { return Point(x - y, x + y); }
    T dot(const Point& rh) const { return x * rh.x + y * rh.y; }
    T det(const Point& rh) const { return x * rh.y - y * rh.x; }
    Point normal() const { return Point(-normalized().y, normalized().x); }
    Point projection(const Point& to) const { return to * (dot(to) / to.norm2()); }
    int quadrant() const {
        if (sgn(y) >= 0) return sgn(x) >= 0 ? 1 : 2;
        return sgn(x) >= 0 ? 4 : 3;
    }
    // 偏角ソート用
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

template <class T>
bool compx(Point<T>& a, Point<T>& b) {
    return a.x < b.x;
}
template <class T>
bool compy(Point<T>& a, Point<T>& b) {
    return a.y < b.y;
}

enum class Turn { Back = -2, CW, Middle, CCW, Front };
/**
 * @brief 辺の曲がる方向
 * @return
 * +1: CCW ab->bcが左に曲がる
 * -1: CW  ab->bcが右に曲がる
 * +2: Front  abの前方
 * -2: Back   abの後方
 *  0: Middle ab上
 */
template <class T>
Turn iSP(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    int flg = sgn((b - a).det(c - a));
    if (flg == 1) {
        return Turn::CCW;
    } else if (flg == -1) {
        return Turn::CW;
    } else {
        if (sgn((b - a).dot(c - b)) > 0) {
            return Turn::Front;
        } else if (sgn((a - b).dot(c - a)) > 0) {
            return Turn::Back;
        } else {
            return Turn::Middle;
        }
    }
}
/**
 * -1: Obtuse 鈍角
 *  0: Right 直角
 * +1: Acute 鋭角
 */
enum class Angle { Obtuse = -1, Right, Acute };
/**
 * @brief 角の種類
 * @return Angle
 * -1: Obtuse 鈍角
 *  0: Right 直角
 * +1: Acute 鋭角
 */
template <class T>
Angle angle_type(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    int t = sgn((a - b).dot(c - b));
    if (t == -1) {
        return Angle::Obtuse;
    } else if (t == 0) {
        return Angle::Right;
    } else {
        return Angle::Acute;
    }
}
}  // namespace bys::geo

namespace bys::geo {
template <class T>
//! @brief 直線
struct Line {
    Point<T> p, q;
    Line(Point<T> p, Point<T> q) : p(p), q(q) {}
    Point<T> to_Point() const { return q - p; }
    Point<ld> to_unit_Point() const { return to_Point().normalized(); }
    ld angle() const { return to_Point().angle(); }
    bool operator==(const Line& rh) const { return abs((int)iSP(p, q, rh.p)) != 1 && abs((int)iSP(p, q, rh.q)) != 1; }
    bool operator!=(const Line& rh) const { return !(*this == rh); }
};
//! @brief 線分
template <class T>
struct Segment : Line<T> {
    Segment(Point<T>& p, Point<T>& q) : Line<T>::Line(p, q) {}
    ld length() const { return this->to_Point().norm(); }
    Point<ld> internal_division(ld m, ld n) const { return (this->p * n + this->q * m) / (m + n); }
    bool operator==(const Segment& rh) const {
        return (this->p == rh.p && this->q == rh.q) || (this->p == rh.q && this->q == rh.p);
    }
    bool operator!=(const Segment& rh) const { return !(*this == rh); }
};
template <class T>
Turn iSP(const Point<T>& p, const Line<T>& l) {
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
    return sgn(a.to_Point().det(b.to_Point())) != 0 || sgn(a.to_Point().det(b.p - a.p)) == 0;
}
template <class T>
bool is_cross(const Segment<T>& a, const Segment<T>& b) {
    return (int)iSP(b.p, a) * (int)iSP(b.q, a) <= 0 && (int)iSP(a.p, b) * (int)iSP(a.q, b) <= 0;
}
template <class T>
ld angle(const Line<T>& a, const Line<T>& b) {
    return std::atan2(a.to_Point().det(b.to_Point()), a.to_Point().dot(b.to_Point()));
}

template <class T>
ld distance(const Point<T>& p, const Line<T>& l) {
    return abs(l.to_Point().det(p - l.p) / (l.q - l.p).norm());
}
template <class T>
ld distance(const Point<T>& p, const Segment<T>& s) {
    if (angle_type(s.p, s.q, p) == Angle::Obtuse) {
        return (p - s.q).norm();
    } else if (angle_type(s.q, s.p, p) == Angle::Obtuse) {
        return (p - s.p).norm();
    } else {
        return distance(p, Line(s.p, s.q));
    }
}
template <class T>
ld distance(const Segment<T>& s, const Segment<T>& t) {
    if (is_cross(s, t)) return 0;

    return min({distance(s.p, t), distance(s.q, t), distance(t.p, s), distance(t.q, s)});
}
template <class T>
std::optional<Point<T>> cross_point(const Line<T>& a, const Line<T>& b) {
    if (!is_cross(a, b)) return std::nullopt;
    return a.p + a.to_Point() * (b.p - a.p).det(b.to_Point()) / a.to_Point().det(b.to_Point());
}
template <class T>
std::optional<Point<T>> cross_point(const Segment<T>& a, const Segment<T>& b) {
    if (!is_cross(a, b)) return std::nullopt;
    return a.p + a.to_Point() * (b.p - a.p).det(b.to_Point()) / a.to_Point().det(b.to_Point());
}
template <class T>
Point<T> projection(const Point<T>& p, const Line<T>& l) {
    return (p - l.p).projection(l.to_Point()) + l.p;
}
template <class T>
Point<T> reflection(const Point<T>& p, const Line<T>& l) {
    return p + (projection(p, l) - p) * 2;
}
}  // namespace bys::geo

/**
 * @todo 半直線の実装
 *
 */

namespace bys {
template <class T>
int bit_width(T x) {
    int bits = 0;
    x = (x < 0) ? (-x) : x;
    for (; x != 0; bits++) x >>= 1;
    return bits;
}
template <class T>
T bit_floor(T x) {
    assert(x >= 0);
    return x == 0 ? 0 : T(1) << (bit_width(x) - 1);
}
template <class T>
T bit_ceil(T x) {
    assert(x >= 0);
    return x == 0 ? 1 : T(1) << bit_width(x - 1);
}

string bin(ll n) {
    assert(n > 0);
    if (n == 0) return "0";
    string res;
    while (n > 0) {
        res.push_back(n & 1 ? '1' : '0');
        n >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}
inline bool pop(int s, int d) { return s & (1 << d); }
inline bool pop(ll s, int d) { return s & (1LL << d); }
}  // namespace bys

namespace bys {
constexpr ll int_pow(int a, int b) {
    ll res = 1;
    for (int i = 0; i < b; ++i) res *= a;
    return res;
}
template <class T>
T mod_pow(T p, T q, T mod) {
    T res = 1 % mod;
    p %= mod;
    for (; q; q >>= 1) {
        if (q & 1) res = res * p % mod;
        p = p * p % mod;
    }
    return res;
}
ll ceildiv(ll x, ll y) { return x > 0 ? (x + y - 1) / y : x / y; }
ll floordiv(ll x, ll y) { return x > 0 ? x / y : (x - y + 1) / y; }
pair<ll, ll> divmod(ll x, ll y) {
    ll q = floordiv(x, y);
    return {q, x - q * y};
}

ll isqrt_aux(ll c, ll n) {
    if (c == 0) return 1;
    ll k = (c - 1) / 2;
    ll a = isqrt_aux(c / 2, n >> (2 * k + 2));
    return (a << k) + (n >> (k + 2)) / a;
}
ll isqrt(ll n) {
    assert(n >= 0);
    if (n == 0) return 0;
    ll a = isqrt_aux((bit_width(n) - 1) / 2, n);
    return n < a * a ? a - 1 : a;
}
template <class T, typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
inline bool isclose(T x, T y, T coef = 4.0) {
    if (x == y) return true;
    auto diff = std::abs(x - y);
    return diff <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * coef || diff < std::numeric_limits<T>::min();
}
}  // namespace bys
namespace bys {
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
}  // namespace bys

namespace bys {
template <class T>
class Combinations {
    const std::vector<T> pool;
    int n, r;
    std::vector<T> comb;
    std::vector<int> indices;
    bool term = false;

   public:
    Combinations(const std::vector<T>& vec, int r) : pool(vec), n(vec.size()), r(r), comb(r), indices(r) {
        if (r > n) {
            term = true;
            return;
        }
        std::iota(indices.begin(), indices.end(), 0);
        for (int i = 0; i < r; ++i) comb[i] = pool[indices[i]];
    }
    Combinations<T> begin() const { return *this; }
    bool end() const { return true; }
    bool operator!=(bool) const { return !term; }
    void operator++() {
        bool flg = true;
        int i = r - 1;
        for (; i >= 0; --i) {
            if (indices[i] != i + n - r) {
                flg = false;
                break;
            }
        }
        if (flg) {
            term = true;
            return;
        }
        indices[i]++;
        for (int j = i + 1; j < r; ++j) {
            indices[j] = indices[j - 1] + 1;
        }
        for (int k = 0; k < r; ++k) comb[k] = pool[indices[k]];
    }
    const std::vector<T>& operator*() const { return comb; }
};
template <std::size_t R>
class IndexCombinations {
    std::array<std::size_t, R> indices;
    std::size_t n, r;
    bool term = false;

   public:
    IndexCombinations(std::size_t n) : n(n), r(indices.size()) {
        if (r > n) {
            term = true;
            return;
        }
        std::iota(indices.begin(), indices.end(), 0);
    }
    IndexCombinations begin() const { return *this; }
    bool end() const { return true; }
    bool operator!=(bool) const { return !term; }
    void operator++() {
        bool flg = true;
        int i = r - 1;
        for (; i >= 0; --i) {
            if (indices[i] != i + n - r) {
                flg = false;
                break;
            }
        }
        if (flg) {
            term = true;
            return;
        }
        indices[i]++;
        for (std::size_t j = i + 1; j < r; ++j) {
            indices[j] = indices[j - 1] + 1;
        }
    }
    const std::array<std::size_t, R>& operator*() const { return indices; }
};
}  // namespace bys

namespace bys {
//! @brief Pythonのrange
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1) : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
    Range(T stop) : it(0), stop(stop), step(1), dir(1) {}
    Range<T> begin() const { return *this; }
    T end() const { return stop; }
    bool operator!=(const T val) const { return (val - it) * dir > 0; }
    void operator++() { it += step; }
    const T& operator*() const { return it; }

   private:
    T it;
    const T stop, step;
    const int dir;

    friend Range reversed(const Range& r) {
        auto new_start = (r.stop - r.dir - r.it) / r.step * r.step + r.it;
        return {new_start, r.it - r.dir, -r.step};
    }
};
template <class T>
Range<T> irange(T stop) {
    return Range(stop);
}
template <class T>
Range<T> irange(T start, T stop, T step = 1) {
    return Range(start, stop, step);
}
}  // namespace bys

namespace bys {
using P = geo::Point<ld>;
pair<P, ld> circle(P a, P b, P c) {
    P amb = (a + b) / 2;
    geo::Line l1(amb, amb + (b - a).rotate90());
    P bnc = (b + c) / 2;
    geo::Line l2(bnc, bnc + (c - b).rotate90());

    auto p = geo::cross_point(l1, l2);
    if (p.has_value()) {
        return {*p, (*p - b).norm()};
    } else {
        return {P(-1, -1), 0};
    }
}

void Solver::solve() {
    constexpr ld EPS = 1e-8;
    auto n = scanner.read<int>();
    auto pos = scanner.readvec<P>(n);
    if (n == 2) EXIT((pos[1] - pos[0]).norm() / 2);

    auto judge = [&](P o, ld r) {
        for (auto&& p : pos) {
            auto d = (p - o).norm();
            if (r < d - EPS) return false;
        }
        return true;
    };

    ld ans = 1e9;
    for (auto [i, j, k] : IndexCombinations<3>(n)) {
        auto [o, r] = circle(pos[i], pos[j], pos[k]);
        if (judge(o, r)) chmin(ans, r);
    }

    for (auto [i, j] : IndexCombinations<2>(n)) {
        auto o = (pos[i] + pos[j]) / 2;
        auto r = (pos[i] - pos[j]).norm() / 2;
        if (judge(o, r)) chmin(ans, r);
    }
    print(ans);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
// [debug] line  46: 487.51154968049 -234.67997268543 577.40159698344
