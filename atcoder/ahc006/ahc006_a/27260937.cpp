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
using Pos = pair<Pa, Pa>;
using Order = pair<pair<Pa, Pa>, int>;
int dist(Pa a, Pa b) {
    return (abs(a.first - b.first) + abs(a.second - b.second));
}
int calc_score(vector<Pos>& root) {
    int n = root.size();
    int res = 0;
    // set<int> recieve;
    for (int i = 0; i < n - 1; ++i) {
        // if (root[i].second.second == 0) {
        //     recieve.insert(root[i].second.first);
        // } else if (root[i].second.second == 1) {
        //     if (recieve.find(root[i].second.first) == recieve.end()) return
        //     INF;
        // }
        res += dist(root[i].first, root[i + 1].first);
    }
    return res;
}
int judge_score(vector<Pos>& root) {
    return std::round(1e8 / (1000 + calc_score(root)));
}
void solve() {
    int ti = std::clock();
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(1, 50);
    Pa office = {400, 400};

    vector<Order> order(1000);
    for (int i = 0; i < 1000; ++i) order[i] = {input<pair<Pa, Pa>>(), i};

    sort(order.begin(), order.end(), [&](Order a, Order b) {
        int a1 = dist(office, a.first.first);
        int a2 = dist(office, a.first.second);
        int b1 = dist(office, b.first.first);
        int b2 = dist(office, b.first.second);
        return a1 * a1 + a2 * a2 < b1 * b1 + b2 * b2;
    });

    vector<int> choice;
    vector<Pos> root;
    root.push_back({office, {-1, -1}});
    for (int i = 0; i < 50; ++i) {
        choice.push_back(order[i].second);
        root.push_back({order[i].first.first, {order[i].second, 0}});
    }
    for (int i = 0; i < 50; ++i) {
        root.push_back({order[i].first.second, {order[i].second, 1}});
    }
    sort(root.begin() + 1, root.begin() + 50,
         [](Pos a, Pos b) { return a.first.first < b.first.first; });
    sort(root.begin() + 51, root.begin() + 100,
         [](Pos a, Pos b) { return a.first.first > b.first.first; });

    root.push_back({office, {-1, -1}});
    int score = calc_score(root);

    while (std::clock() - ti < 195 * CLOCKS_PER_SEC / 100) {
        // int l = distr(eng);
        // int r = distr(eng);
        // if (l == r) continue;
        // std::swap(root[l], root[r]);
        // if (!chmin(score, calc_score(root))) std::swap(root[l], root[r]);
        int l = distr(eng);
        int r = distr(eng);
        if (l == r) continue;
        std::swap(root[l], root[r]);
        if (!chmin(score, calc_score(root))) std::swap(root[l], root[r]);

        l += 50;
        r += 50;
        std::swap(root[l], root[r]);
        if (!chmin(score, calc_score(root))) std::swap(root[l], root[r]);
    }

    for (auto&& ci : choice) ci++;
    print(choice.size(), choice);
    vector<Pa> root_ans;
    for (auto&& ri : root) root_ans.push_back(ri.first);
    print(root.size(), root_ans);
    DEBUG(judge_score(root));
}
}  // namespace bys

int main() {
    bys::init();
    bys::solver(/* bys::input<int>() */);
    return 0;
}
