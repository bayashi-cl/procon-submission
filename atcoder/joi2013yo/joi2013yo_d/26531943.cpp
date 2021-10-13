#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
#include <atcoder/math>
#include <atcoder/modint>
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
using atcoder::pow_mod, atcoder::inv_mod;
using std::array, std::vector, std::string, std::set, std::map, std::pair;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::reverse, std::abs, std::pow;

// alias
using mint = atcoder::modint998244353;
using ll = long long int;
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
// modint
inline std::istream& operator>>(std::istream& is, mint& m) {
    ll n;
    is >> n;
    m = n;
    return is;
}
inline std::ostream& operator<<(std::ostream& os, const mint& m) {
    return os << m.val();
}

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
    // if (!container.empty()) {
    //     std::copy(
    //         std::begin(container), std::prev(std::end(container)),
    //         std::ostream_iterator<
    //             const typename std::remove_reference<C>::type::value_type&>{
    //             os, " "});
    //     std::cout << *std::prev(std::end(container));
    // }
    // return os;
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
    // std::copy_n(std::istream_iterator<
    //                 typename std::remove_reference<C>::type::value_type>(is),
    //             std::size(container), std::begin(container));
    // return is;
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
template <class... Args>
std::tuple<Args...> input() {
    std::tuple<Args...> res;
    std::apply([](Args&... args) { (cin >> ... >> args); }, res);
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
inline bool pop(int s, int d) { return s & (1 << d); }

// config
inline void init() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

}  // namespace bys

using namespace bys;
void solve() {
    auto [d, n] = input<int, 2>();
    auto t = input<int>(d);
    auto cand = input<array<int, 3>>(n);
    VecVec dp(d, Vec(n, -INF));

    for (int i = 0; i < n; ++i) {
        auto [a, b, c] = cand[i];
        if (a <= t[0] && t[0] <= b) dp[0][i] = 0;
    }

    for (int i = 1; i < d; ++i) {
        int temp = t[i];
        for (int j = 0; j < n; ++j) {
            if (temp < cand[j][0] || cand[j][1] < temp) continue;
            for (int k = 0; k < n; ++k) {
                chmax(dp[i][j], dp[i - 1][k] + abs(cand[j][2] - cand[k][2]));
            }
        }
    }
    print(*std::max_element(std::begin(dp.back()), std::end(dp.back())));
}

int main() {
    bys::init();
    solve();
    return 0;
}
