#line 1 "joi2020_yo2_a/main.cpp"
// #include "byslib/linalg.hpp"
#line 2 "byslib/matrix.hpp"
#include <valarray>

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
    if (container.empty()) return os;
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
template <class T>
inline vector<vector<T>> input(int n, int m) {
    vector res(n, vector<T>(m));
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
inline bool pop(ll s, int d) { return s & (1LL << d); }

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
// clang-format off
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on

// solver
// void solve();
// void solver(int t = 1) {
//     for (int i = 0; i < t; ++i) solve();
// }
struct Solver {
    Solver() { init(); }
    void solve();
    void solve(int rep) {
        for (int i = 0; i < rep; ++i) solve();
    }
};
}  // namespace bys
#line 5 "byslib/matrix.hpp"
namespace bys {
using std::valarray;
template <class T>
struct Matrix {
    valarray<valarray<T>> mat;
    int row, col;
    Matrix(int row_, int col_) {
        row = row_;
        col = col_;
        mat = valarray<valarray<T>>(valarray<T>(col), row);
    }

    valarray<T>& operator[](int k) { return mat[k]; }
    void set(int i, int j, T v) { mat[i][j] = v; }
    pair<int, int> shape() const { return {row, col}; }

    Matrix transpose() const {
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                res.mat[j][i] = mat[i][j];
            }
        }
    }
    Matrix rotate() const {
        Matrix<T> res(col, row);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                res.mat[j][row - i - 1] = mat[i][j];
            }
        }
        return res;
    }

    Matrix operator+(const Matrix<T>& rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] + rh.mat[i];
        }
        return res;
    }
    Matrix operator+(const T rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] + rh;
        }
        return res;
    }
    Matrix operator+=(const Matrix<T>& rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] += rh.mat[i];
        }
        return *this;
    }
    Matrix operator+=(const T rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] += rh;
        }
        return *this;
    }
    Matrix operator-(const Matrix<T>& rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] - rh.mat[i];
        }
        return res;
    }
    Matrix operator-(const T rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] - rh;
        }
        return res;
    }
    Matrix operator-=(const Matrix<T>& rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] -= rh.mat[i];
        }
        return *this;
    }
    Matrix operator-=(const T rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] -= rh;
        }
        return *this;
    }

    Matrix operator*(const Matrix<T>& rh) const {
        auto rht = rh.transpose();
        assert(shape() == rht.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                res.mat[i][j] = (mat[i] * rht.mat[j]).sum();
            }
        }
        return res;
    }
    Matrix operator*(const T rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] * rh;
        }
        return res;
    }
    // Matrix operator*=(const Matrix<T>& rh) {
    //     assert(shape() == rh.shape());
    //     for (int i = 0; i < row; ++i) {
    //         mat[i] += rh.mat[i];
    //     }
    //     return *this;
    // }
    Matrix operator*=(const T rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] *= rh;
        }
        return *this;
    }
    Matrix operator/(const T rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] / rh;
        }
        return res;
    }
    Matrix operator/=(const T rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] /= rh;
        }
        return *this;
    }
    Matrix operator%(const T rh) const {
        assert(shape() == rh.shape());
        Matrix<T> res(row, col);
        for (int i = 0; i < row; ++i) {
            res.mat[i] = mat[i] % rh;
        }
        return res;
    }
    Matrix operator%=(const T rh) {
        assert(shape() == rh.shape());
        for (int i = 0; i < row; ++i) {
            mat[i] %= rh;
        }
        return *this;
    }
};
template <class T>
Matrix<T> pow(const Matrix<T>& mat, int p) {
    auto [c, r] = mat.shape();
    Matrix<T> res(c, r);
    return res;
}
}  // namespace bys
#line 4 "joi2020_yo2_a/main.cpp"

namespace bys {
void Solver::solve() {
    auto n = input<int>();
    auto s_ = input<string>(n);
    auto t_ = input<string>(n);
    Matrix<int> s(n, n), t(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (s_[i][j] == 'R') {
                s[i][j] = 0;
            } else if (s_[i][j] == 'G') {
                s[i][j] = 1;
            } else if (s_[i][j] == 'B') {
                s[i][j] = 2;
            }
            if (t_[i][j] == 'R') {
                t[i][j] = 0;
            } else if (t_[i][j] == 'G') {
                t[i][j] = 1;
            } else if (t_[i][j] == 'B') {
                t[i][j] = 2;
            }
        }
    }

    array ans = {0, 1, 2, 1};
    for (int r = 0; r < 4; ++r) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (s[i][j] != t[i][j]) ans[r]++;
            }
        }
        s = s.rotate();
    }
    print(*std::min_element(ans.begin(), ans.end()));
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
