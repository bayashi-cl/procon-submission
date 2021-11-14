#line 1 "ahc006_a/main.cpp"
#include <random>

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
// clang-format off
#define EXIT(...) { print(__VA_ARGS__); return; }
// clang-format on

// solver
void solve();
void solver(int t = 1) {
    for (int i = 0; i < t; ++i) solve();
}
}  // namespace bys
#line 4 "ahc006_a/main.cpp"

namespace bys {
int dist(Pa a, Pa b) {
    return (abs(a.first - b.first) + (a.second - b.second));
}
int score(vector<Pa>& root) {
    int n = root.size();
    int res = 0;
    for (int i = 0; i < n - 1; ++i) res += dist(root[i], root[i + 1]);
    return res;
}
int judge_score(vector<Pa>& root) {
    return std::round(1e8 / (1000 + score(root)));
}
void solve() {
    // int ti = std::clock();
    // std::random_device seed_gen;
    // std::mt19937 engine{seed_gen()};

    using Order = pair<pair<Pa, Pa>, int>;
    Pa office = {400, 400};

    vector<Order> order(1000);
    for (int i = 0; i < 1000; ++i) order[i] = {input<pair<Pa, Pa>>(), i};

    sort(order.begin(), order.end(), [&](Order a, Order b) {
        return dist(office, a.first.first) + dist(office, a.first.second) <
               dist(office, b.first.first) + dist(office, b.first.second);
    });

    vector<int> choice;
    vector<Pa> root;
    root.push_back({400, 400});
    for (int i = 0; i < 50; ++i) {
        choice.push_back(order[i].second);
        root.push_back(order[i].first.first);
        root.push_back(order[i].first.second);
    }
    root.push_back({400, 400});

    // while (std::clock() - ti < 190 * CLOCKS_PER_SEC / 100) {
    //     Vec choice_;
    //     std::sample(idx.begin(), idx.end(), std::back_inserter(choice_), 50,
    //                 engine);
    //     vector<Pa> root;
    //     set<int> choice;
    //     for (auto&& ci : choice_) choice.insert(ci);
    //     for (auto&& ci : choice_) {
    //         root.push_back(order[ci].first);
    //         root.push_back(order[ci].second);
    //     }
    //     root.push_back({400, 400});
    //     if (chmin(min_score, score(root))) {
    //         ans_choice = choice;
    //         ans_root = root;
    //     }
    // }
    for (auto&& ci : choice) ci++;
    print(choice.size(), choice);
    print(root.size(), root);
    DEBUG(judge_score(root));
}
}  // namespace bys

int main() {
    bys::init();
    bys::solver(/* bys::input<int>() */);
    return 0;
}
