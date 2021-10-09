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
using ll = long long;
using Pa = pair<int, int>;
using Vec = vector<int>;
using VecVec = std::vector<Vec>;
template <class T>
using uset = std::unordered_set<T>;
template <class S, class T>
using umap = std::unordered_map<S, T>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;

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
    if (!container.empty()) {
        std::copy(
            std::begin(container), std::prev(std::end(container)),
            std::ostream_iterator<
                const typename std::remove_reference<C>::type::value_type&>{
                os, " "});
        std::cout << *std::prev(std::end(container));
    }
    return os;
}

template <typename C,
          typename std::enable_if<is_container<C>::value &&
                                      !std::is_same<C, std::string>::value &&
                                      !std::is_same<C, std::wstring>::value,
                                  std::nullptr_t>::type = nullptr>
std::istream& operator>>(std::istream& is, C& container) {
    std::copy_n(std::istream_iterator<
                    typename std::remove_reference<C>::type::value_type>(is),
                std::size(container), std::begin(container));
    return is;
}

// -------------- I/O helper --------------
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

// -------------- Utility --------------
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

void init() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    cout << std::fixed << std::setprecision(11);
    std::cerr << std::boolalpha;
}

// -------------- macro --------------
#ifdef LOCAL
#define DEBUG(...) debug("[debug] line:", __LINE__, "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif
#define EXIT(msg)   \
    {               \
        print(msg); \
        return;     \
    }
}  // namespace bys

namespace bys {

struct Board {
    int h, w;
    Board(int row, int col) : h(row), w(col) {}

    bool contain(int row, int col) {
        return 0 <= row && row < h && 0 <= col && col < w;
    }
    vector<pair<int, int>> next(int i, int j,
                                const vector<pair<int, int>> delta = {
                                    {1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
        vector<pair<int, int>> res;
        for (auto [di, dj] : delta) {
            int ni = i + di;
            int nj = j + dj;
            if (contain(ni, nj)) res.push_back({ni, nj});
        }
        return res;
    }
    int index(int i, int j) { return i * w + j; }
    int area() { return h * w; }
};

int bfs(VecVec& graph) {
    int n = graph.size();
    vector<int> cost(n, INF);
    std::queue<int> que;
    que.push(0);
    cost[0] = 1;

    while (!que.empty()) {
        int from = que.front();
        que.pop();
        for (auto&& to : graph[from]) {
            if (cost[to] != INF) continue;
            cost[to] = cost[from] + 1;
            que.push(to);
        }
    }
    return cost.back() == INF ? 0 : cost.back();
}

void solve() {
    while (true) {
        auto [w, h] = input<int, 2>();
        if (w == 0 && h == 0) break;

        VecVec hor(h - 1, Vec(w)), var(h, Vec(w - 1));
        Board brd(h, w);
        VecVec adj(brd.area());

        for (int i = 0; i < h - 1; ++i) {
            cin >> var[i] >> hor[i];
        }
        cin >> var[h - 1];

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w - 1; ++j) {
                if (var[i][j] == 0) {
                    int f = brd.index(i, j);
                    int t = brd.index(i, j + 1);
                    adj[f].push_back(t);
                    adj[t].push_back(f);
                }
            }
        }
        for (int i = 0; i < h - 1; ++i) {
            for (int j = 0; j < w; ++j) {
                if (hor[i][j] == 0) {
                    int f = brd.index(i, j);
                    int t = brd.index(i + 1, j);
                    adj[f].push_back(t);
                    adj[t].push_back(f);
                }
            }
        }
        print(bfs(adj));
    }
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
}

