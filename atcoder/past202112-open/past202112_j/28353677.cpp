#line 2 "/home/bayashi/dev/byslib/core/stdlib.hpp"
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
using Pall = pair<ll, ll>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/const.hpp"

namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/io.hpp"

namespace bys {
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
    static auto check(T&& obj) -> decltype(obj.begin(), obj.end(), std::true_type{});
    template <typename T>
    static auto check(...) -> std::false_type;
};
template <typename T>
class is_container : public decltype(is_container_impl::check<T>(std::declval<T>())) {};

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::ostream& operator<<(std::ostream& os, const C& container) noexcept {
    if (container.empty()) return os;
    std::for_each(std::begin(container), std::prev(std::end(container)), [&](auto e) { os << e << ' '; });
    return os << *std::prev(std::end(container));
}

template <typename C, typename std::enable_if<is_container<C>::value && !std::is_same<C, std::string>::value &&
                                                  !std::is_same<C, std::wstring>::value,
                                              std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::for_each(std::begin(container), std::end(container), [&](auto&& e) { is >> e; });
    return is;
}

// I/O helper
//! @brief 任意の型を1つ
template <class T>
inline T input() {
    T n;
    cin >> n;
    return n;
}
//! @brief 任意の型がn要素のvector
template <class T>
inline vector<T> input(int n) {
    vector<T> res(n);
    cin >> res;
    return res;
}
//! @brief 任意の型がn行m列のvector
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
    cin >> res;
    return res;
}

//! @brief 任意の型をN個 受け取りは構造化束縛で
template <class T, size_t N>
inline std::array<T, N> input() {
    std::array<T, N> res;
    cin >> res;
    return res;
}
//! @brief 2つ以上の異なる型 受け取りは構造化束縛で
template <class S, class T, class... Us>
std::tuple<S, T, Us...> input() {
    std::tuple<S, T, Us...> res;
    std::apply([](auto&... e) { (cin >> ... >> e); }, res);
    return res;
}
//! @brief 標準入力から代入
template <class... Ts>
void cinto(Ts&... args) {
    (cin >> ... >> args);
}
//! @brief pythonのprintっぽい挙動をする
struct Print {
    std::ostream& os;
    string sep = " ", end = "\n";
    Print(std::ostream& os) : os(os) {}
    ~Print() { os << std::flush; }
    void operator()() { os << end; }
    template <class T>
    void operator()(const T& a) {
        os << a << end;
    }
    //! @brief 空白区切りで出力
    template <class T, class... Ts>
    void operator()(const T& a, const Ts&... b) {
        os << a;
        (os << ... << (os << sep, b));
        os << end;
    }
    //! @brief 出力後flush インタラクティブ問題用
    template <class... Ts>
    void send(const Ts&... a) {
        operator()(a...);
        os << std::flush;
    }
} print(std::cout), debug(std::cerr);

//! @brief cin高速化など
inline void fastio() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/core/macro.hpp"

// clang-format off
#ifdef LOCAL
//! @brief デバッグ用出力 ジャッジ上では何もしない。
#define DEBUG(...) debug("[debug] line:", __LINE__, "\t", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
//! @brief printしてreturnする。
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on
#line 3 "/home/bayashi/dev/byslib/core/solver.hpp"

namespace bys {
struct Solver {
    int IT = 1;
    Solver() { fastio(); }
    void solve();
    void solve(int rep) {
        for (; IT <= rep; ++IT) solve();
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/math/matrix.hpp"

// TODO: geoとの連携

namespace bys {
template <class T>
struct Matrix {
    vector<vector<T>> mat;
    Matrix(int i, int j) : mat(i, vector<T>(j)), r(i), c(j) {}
    Matrix(const vector<vector<T>>& v) : mat(v), r(v.size()), c(v[0].size()) {}

    vector<T>& operator[](int k) { return mat[k]; }
    int row() const { return r; }
    int col() const { return c; }
    pair<int, int> shape() const { return {r, c}; }

    Matrix operator+(const Matrix<T>& rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(r, c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = mat[i][j] + rh.mat[i][j];
            }
        }
        return res;
    }
    Matrix operator-(const Matrix<T>& rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(r, c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = mat[i][j] - rh.mat[i][j];
            }
        }
        return res;
    }
    Matrix operator*(const T rh) const {
        Matrix<T> res(r, c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = mat[i][j] * rh;
            }
        }
        return res;
    }
    Matrix operator/(const T rh) const {
        Matrix<T> res(r, c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = mat[i][j] / rh;
            }
        }
        return res;
    }

    Matrix operator*(const Matrix<T>& rh) const {
        assert(col() == rh.row());
        int k = rh.col();
        Matrix<T> res(r, k);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < k; ++j) {
                for (int k = 0; k < c; ++k) {
                    res.mat[i][j] += mat[i][k] * rh.mat[k][j];
                }
            }
        }
        return res;
    }
    vector<T> operator*(const vector<T>& rh) const {
        int n = rh.size();
        assert(col() == n);
        vector<T> res(r);
        for (int i = 0; i < r; ++i) {
            res[i] = std::inner_product(mat[i].begin(), mat[i].end(), rh.begin(), (T)0);
        }
        return res;
    }

    Matrix rotate90() const {
        Matrix<T> res(c, r);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res.mat[j][r - i - 1] = mat[i][j];
            }
        }
        return res;
    }

    static Matrix<T> ident(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) res.mat[i][i] = 1;
        return res;
    }
    static Matrix<double> rotate(double theta) {
        Matrix<double> res(2, 2);
        res[0][0] = std::cos(theta);
        res[0][1] = -std::sin(theta);
        res[1][0] = std::sin(theta);
        res[1][1] = std::cos(theta);
        return res;
    }

   private:
    int r, c;
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/math/affine.hpp"

namespace bys::affine {
Matrix<ll> ident() { return Matrix<ll>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}); }
Matrix<ll> rot_cw() { return Matrix<ll>({{0, -1, 0}, {1, 0, 0}, {0, 0, 1}}); }
Matrix<ll> rot_ccw() { return Matrix<ll>({{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}}); }
Matrix<ll> rev_xaxis() { return Matrix<ll>({{1, 0, 0}, {0, -1, 0}, {0, 0, 1}}); }
Matrix<ll> rev_yaxis() { return Matrix<ll>({{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}}); }
Matrix<ll> move(ll x, ll y) { return Matrix<ll>({{1, 0, x}, {0, 1, y}, {0, 0, 1}}); }

Matrix<ll> grid_rot_cw(int h, int w) { return Matrix<ll>({{0, 1, 0}, {-1, 0, w - 1}, {0, 0, 1}}); }
Matrix<ll> grid_rot_ccw(int h, int w) { return Matrix<ll>({{0, -1, h - 1}, {1, 0, 0}, {0, 0, 1}}); }
Matrix<ll> grid_rev_row(int h, int w) { return Matrix<ll>({{-1, 0, h - 1}, {0, 1, 0}, {0, 0, 1}}); }
Matrix<ll> grid_rev_col(int h, int w) { return Matrix<ll>({{1, 0, 0}, {0, -1, w - 1}, {0, 0, 1}}); }

pair<ll, ll> transform(const Matrix<ll>& mat, ll x, ll y) {
    vector<ll> v = {x, y, 1};
    vector<ll> res = mat * v;
    return {res[0], res[1]};
}

}  // namespace bys::affine
#line 2 "/home/bayashi/dev/byslib/utility/range.hpp"

namespace bys {
//! @brief pythonのrangeと同じ挙動
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
}  // namespace bys
#line 4 "past202112_j/main.cpp"

namespace bys {
void Solver::solve() {
    auto [n, q] = input<int, 2>();
    vector grid(n, vector(n, 0));
    Matrix<ll> tr = affine::ident();
    Matrix<ll> tr_inv = affine::ident();
    Matrix<ll> m_2a = affine::grid_rot_cw(n, n);
    Matrix<ll> m_2b = affine::grid_rot_ccw(n, n);
    Matrix<ll> m_3a = affine::grid_rev_row(n, n);
    Matrix<ll> m_3b = affine::grid_rev_col(n, n);
    for (int qi = 0; qi < q; ++qi) {
        auto t = input<int>();
        if (t == 1) {
            auto [i, j] = input<int, 2>();
            --i, --j;
            auto [i0, j0] = affine::transform(tr_inv, i, j);
            grid[i0][j0] = 1 - grid[i0][j0];
        } else if (t == 2) {
            auto c = input<char>();
            if (c == 'A') {
                tr = m_2a * tr;
                tr_inv = tr_inv * m_2b;
            } else {
                tr = m_2b * tr;
                tr_inv = tr_inv * m_2a;
            }
        } else {
            auto c = input<char>();
            if (c == 'A') {
                tr = m_3a * tr;
                tr_inv = tr_inv * m_3a;
            } else {
                tr = m_3b * tr;
                tr_inv = tr_inv * m_3b;
            }
        }
    }
    vector ans(n, vector(n, 0));
    for (int i : Range(n)) {
        for (int j : Range(n)) {
            auto [i0, j0] = affine::transform(tr, i, j);
            ans[i0][j0] = grid[i][j];
        }
    }
    for (auto&& e : ans) {
        for (auto&& f : e) {
            cout << f;
        }
        cout << endl;
    }
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
