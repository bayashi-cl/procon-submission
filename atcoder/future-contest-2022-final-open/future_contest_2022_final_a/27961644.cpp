#line 1 "future_contest_2022_final_a/main.cpp"
#include <random>

// #include "byslib/graph/depth_first.hpp"
#line 2 "/home/bayashi/dev/byslib/byslib/template/bys.hpp"
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
    string sep = " ", end = "\n";
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
    template <class... Ts>
    void send(const Ts&... a) {
        operator()(a...);
        os << std::flush;
    }
} print(std::cout), debug(std::cerr);

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
template <typename T>
struct Range {
    Range(T start, T stop, T step = 1)
        : it(start), stop(stop), step(step), dir(step >= 0 ? 1 : -1) {}
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
struct Solver {
    Solver() { init(); }
    void solve();
    void solve(int rep) {
        for (int i = 0; i < rep; ++i) solve();
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/byslib/graph/edge.hpp"

namespace bys {
struct Edge {
    int from, to;
    ll cost;
    // 重みなし単頂点
    Edge(int to) : from(-1), to(to), cost(1) {}
    // 重み付き単頂点
    Edge(int to, ll cost) : from(-1), to(to), cost(cost) {}
    // 重み付き両頂点
    Edge(int from, int to, ll cost) : from(from), to(to), cost(cost) {}
    bool operator<(const Edge& rh) const { return cost < rh.cost; }
    friend std::ostream& operator>>(std::ostream& os, const Edge& e) {
        return os << e.from << " - " << e.to << ": " << e.cost;
    }
};
using Adj = vector<vector<Edge>>;
}  // namespace bys
#line 4 "/home/bayashi/dev/byslib/byslib/graph/warshall_floyd.hpp"

namespace bys {
struct WarshallFloyd {
    int n_node;
    vector<vector<ll>> cost;
    vector<vector<int>> prev;

    WarshallFloyd(const Adj& graph)
        : n_node(graph.size()),
          cost(n_node, vector(n_node, LINF)),
          prev(n_node, vector(n_node, -1)) {
        for (int i = 0; i < n_node; ++i) {
            for (auto e : graph[i]) cost[i][e.to] = e.cost;
        }
        for (int i = 0; i < n_node; ++i) cost[i][i] = 0;
        for (int i = 0; i < n_node; ++i) {
            for (int j = 0; j < n_node; ++j) {
                prev[i][j] = i;
            }
        }
        search();
    }

    void search() {
        for (int k = 0; k < n_node; k++) {
            for (int i = 0; i < n_node; i++) {
                for (int j = 0; j < n_node; j++) {
                    if (chmin(cost[i][j], cost[i][k] + cost[k][j])) {
                        prev[i][j] = prev[k][j];
                    };
                }
            }
        }
    }
    vector<int> path(int from, int to) {
        vector<int> res;
        for (int now = to; now != from; now = prev[from][now]) {
            res.push_back(now);
        }
        res.push_back(from);
        std::reverse(res.begin(), res.end());
        return res;
    }
};
}  // namespace bys
#line 1 "/home/bayashi/dev/byslib/byslib/template/marathon.hpp"
#include <chrono>

namespace bys {
struct Timer {
    std::chrono::time_point<std::chrono::system_clock> end;
    Timer(int ms) {
        end = std::chrono::system_clock::now() + std::chrono::milliseconds(ms);
    }
    inline bool counting() const {
        return std::chrono::system_clock::now() <= end;
    }
};
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/byslib/util.hpp"

namespace bys {
template <class T, std::size_t I>
struct ItemGetter {
    bool operator()(const T& lh, const T& rh) { return lh[I] < rh[I]; }
};

/**
 * @brief 二分探索法
 * https://atcoder.jp/contests/abc205/submissions/23500985
 * @tparam T 初期値と返り値、is_okの第一引数 int or long long intを想定
 * @param ok (T): is_okを満たす初期値
 * @param ng (T): is_okを満たさない初期値
 * @param is_ok (bool()): 判定用ラムダ式
 * @param args... (Args...): is_okに渡される引数 可変長
 * @return (T): is_okを満たす最大/小の整数
 */
template <typename T, class Lambda, class... Args>
T meguru_bisect(T ok, T ng, Lambda is_ok, Args... args) {
    assert(is_ok(ok, args...));
    assert(!is_ok(ng, args...));

    while (std::abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        if (is_ok(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

template <class Lambda, class... Args>
double bisect_float(double ok, double ng, int rep, Lambda is_ok, Args... args) {
    assert(is_ok(ok, args...));
    assert(!is_ok(ng, args...));

    for (int i = 0; i < rep; i++) {
        double mid = (ok + ng) / 2;
        if (is_ok(mid, args...)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

template <class T>
struct Compress {
    vector<T> cp;
    bool build = false;
    Compress() {}
    Compress(vector<T>& vec) : cp(vec) {}
    void add(T v) {
        assert(!build);
        cp.push_back(v);
    }
    void construct() {
        assert(!build);
        sort(std::begin(cp), std::end(cp));
        cp.erase(std::unique(std::begin(cp), std::end(cp)), cp.end());
        build = true;
    }
    int get(T v) const {
        assert(build);
        auto itr = std::lower_bound(std::begin(cp), std::end(cp), v);
        assert(*itr == v);
        return std::distance(cp.begin(), itr);
    }
    int size() const { return cp.size(); }
    T unzip(int i) {
        assert(build);
        return cp[i];
    }
};

template <class T>
T cumulate(vector<T>& vec, T init = 0) {
    T sum = init;
    for (auto&& i : vec) {
        sum += i;
        i = sum;
    }
    return sum;
}

template <class T, class BinOp>
T cumulate(vector<T>& vec, BinOp op, T init = 0) {
    T sum = init;
    for (auto&& i : vec) {
        sum = op(sum, i);
        i = sum;
    }
    return sum;
}

struct Grid {
    int h, w;
    Grid(int row, int col) : h(row), w(col) {}

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

template <class T>
struct CumulativeSum {
    vector<T> data;
    CumulativeSum(int n) : data(n + 1){};
    CumulativeSum(const vector<T>& v) : data(v.size() + 1) {
        std::copy(v.begin(), v.end(), std::next(data.begin()));
    };
    void set(int i, int x) {
        assert(!build);
        data[i + 1] = x;
    }
    void construct() {
        assert(!build);
        std::partial_sum(data.begin(), data.end(), data.begin());
        build = true;
    }
    // [l, r)
    T sum(int l, int r) {
        assert(build);
        if (l > r) return 0;
        return data[r] - data[l];
    }

   private:
    bool build = false;
};
template <class T>
struct CumulativeSum2D {
    vector<vector<T>> data;
    CumulativeSum2D(int n, int m) : data(n + 1, vector<T>(m + 1)){};
    CumulativeSum2D(const vector<vector<T>>& v)
        : data(v.size() + 1, vector<T>(v[0].size() + 1)) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            std::copy(v[i].begin(), v[i].end(), std::next(data[i + 1].begin()));
        }
    };
    void set(int i, int j, int x) {
        assert(!build);
        data[i + 1][j + 1] = x;
    }
    T get(int i, int j) const { return data[i + 1][j + 1]; }
    void construct() {
        assert(!build);
        int n = data.size();
        int m = data[0].size();
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                data[i][j] +=
                    data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
            }
        }
        build = true;
    }
    // [si, gi), [sj, gj)
    T sum(int si, int sj, int gi, int gj) {
        assert(build);
        return (data[gi][gj] - data[si][gj] - data[gi][sj] + data[si][sj]);
    }
    // [s, g)
    T sum(pair<int, int> s, pair<int, int> g) {
        return sum(s.first, s.second, g.first, g.second);
    }

   private:
    bool build = false;
};
}  // namespace bys
#line 9 "future_contest_2022_final_a/main.cpp"

namespace bys {
const int N = 20;
enum class Dir { North, East, South, West, Err };

// 隣接する2地点の位置関係を返す
Dir direction(int from, int to) {
    if (from + 1 == to) {
        return Dir::East;
    } else if (from - 1 == to) {
        return Dir::West;
    } else if (from + N == to) {
        return Dir::South;
    } else if (from - N == to) {
        return Dir::North;
    } else {
        return Dir::Err;
    }
}

// 方向転換のコマンドを返す
string rotate(Dir from_dir, Dir to_dir) {
    string res;
    int diff = (int)to_dir - (int)from_dir;
    if (from_dir == to_dir) {
    } else if (abs(diff) == 2) {
        res = "RR";
    } else if (diff == 1 || diff == -3) {
        res = "R";
    } else if (diff == -1 || diff == 3) {
        res = "L";
    }
    return res;
}

// 隣接する2地点を移動するコマンドと移動後の方向を返す
pair<string, Dir> mv(int from, int to, Dir now_dir) {
    Dir for_dir = direction(from, to);
    assert(for_dir != Dir::Err);
    string res = rotate(now_dir, for_dir);
    res.push_back('F');
    return {res, for_dir};
}

// 任意の2地点間を移動するコマンドと移動後の方向を返す
pair<string, Dir> a2b(const vector<int>& path, Dir now_dir) {
    // auto path = wf.path(from, to);
    int sz = path.size();
    string res;
    for (int i : Range(sz - 1)) {
        auto [com, d] = mv(path[i], path[i + 1], now_dir);
        now_dir = d;
        res += com;
    }
    return {res, now_dir};
}

struct DepthFirstSearch {
    const Adj& graph;
    vector<bool> seen;
    vector<int> pre_order;
    vector<int> post_order;
    vector<int> tour;

    DepthFirstSearch(const Adj& graph, int start)
        : graph(graph), seen(graph.size()) {
        search(start, Dir::North);
    }

    void search(int now, Dir dir) {
        seen[now] = true;
        pre_order.push_back(now);
        tour.push_back(now);
        auto adj = graph[now];
        for (int i : Range(1, (int)adj.size())) {
            if (direction(now, adj[i].to) == dir) {
                std::swap(adj[i], adj[0]);
            }
        }
        for (auto&& to : adj) {
            if (seen[to.to]) continue;
            search(to.to, direction(now, to.to));
            tour.push_back(now);
        }
        post_order.push_back(now);
    }
};

// ランレングス圧縮
string golf(const string& s) {
    std::stringstream ss;
    char c = s[0];
    int cnt = 0;
    for (auto&& si : s) {
        if (si == c) {
            ++cnt;
        } else {
            if (cnt == 1) {
                ss << c;
            } else {
                ss << cnt << c;
            }
            cnt = 1;
            c = si;
        }
    }
    if (cnt == 1) {
        ss << c;
    } else {
        ss << cnt << c;
    }
    return ss.str();
}

int calc_score(int l) { return N * N + (int)std::round(1e8 / (100 + l)); }

void Solver::solve() {
    Timer timer(1995);
    auto [si, sj] = input<int, 2>();
    auto h = input<string>(N);
    auto v = input<string>(N - 1);
    Grid grid(N, N);
    int s = grid.index(si, sj);

    // 乱数生成器
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(1, 398);

    // 隣接グラフ
    Adj graph(grid.area());
    for (int i : Range(N)) {
        for (int j : Range(N - 1)) {
            if (h[i][j] == '0') {
                int f = grid.index(i, j);
                int t = grid.index(i, j + 1);
                graph[f].push_back({t});
                graph[t].push_back({f});
            }
        }
    }
    for (int i : Range(N - 1)) {
        for (int j : Range(N)) {
            if (v[i][j] == '0') {
                int f = grid.index(i, j);
                int t = grid.index(i + 1, j);
                graph[f].push_back({t});
                graph[t].push_back({f});
            }
        }
    }

    DepthFirstSearch dfs(graph, s);
    auto order = dfs.pre_order;
    WarshallFloyd wf(graph);

    auto get_com = [&]() -> string {
        Dir dir = Dir::North;
        string temp_ans;
        for (int i : Range((int)order.size() - 1)) {
            auto [com, d] = a2b(wf.path(order[i], order[i + 1]), dir);
            dir = d;
            temp_ans += com;
        }
        temp_ans = golf(temp_ans);
        return temp_ans;
    };

    string ans = get_com();
    std::size_t len = ans.length();
    while (timer.counting()) {
        int i = distr(eng);
        std::swap(order[i], order[i + 1]);
        auto dans = get_com();
        if (chmin(len, dans.length())) {
            // debug("inc");
            ans = dans;
        } else {
            std::swap(order[i], order[i + 1]);
        }
    }
    print(ans);
    // debug(calc_score(ans.length()));
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::input<int>() */);
    return 0;
}
