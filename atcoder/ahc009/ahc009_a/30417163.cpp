#include <random>

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
#include <chrono>

namespace bys {
struct Timer {
    std::chrono::time_point<std::chrono::system_clock> end;
    Timer(int ms) { end = std::chrono::system_clock::now() + std::chrono::milliseconds(ms); }
    inline bool counting() const { return std::chrono::system_clock::now() <= end; }
};
}  // namespace bys
namespace bys {
struct Edge {
    std::size_t src, dest;
    ll weight;
    Edge() {}
    Edge(std::size_t src, std::size_t dest, ll weight = 1) : src(src), dest(dest), weight(weight) {}
    bool operator<(const Edge& rh) const { return weight < rh.weight; }
    operator int() const { return dest; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        return os << "{" << e.src << " -> " << e.dest << ": " << e.weight << "}";
    }
};
struct DynamicAdjacencyList {
    std::vector<std::vector<Edge>> data;
    DynamicAdjacencyList(std::size_t n) : data(n, vector<Edge>()), _n(n) {}
    std::vector<vector<Edge>>::reference operator[](std::size_t i) { return *(data.begin() + i); }
    const std::vector<vector<Edge>>::const_reference operator[](std::size_t i) const { return *(data.cbegin() + i); }
    void add_edge(const Edge& e) { data[e.src].push_back(e); }
    void add_edge(std::size_t src, std::size_t dest, ll weight = 1) { data[src].push_back({src, dest, weight}); }
    std::size_t size() const { return _n; }

   private:
    std::size_t _n;
};
struct AdjacencyList {
    AdjacencyList(std::size_t n, std::size_t m) : _n(n), _m(m), index(n + 1), _build_flg(m == 0) { buf.reserve(m); }

    struct AdjacencyRange {
        using iterator = std::vector<Edge>::const_iterator;
        using reference = std::vector<Edge>::const_reference;
        iterator _begin, _end;
        iterator begin() const { return _begin; }
        iterator end() const { return _end; }
        reference operator[](std::size_t i) const { return *(_begin + i); }
        std::size_t size() const { return std::distance(_begin, _end); }
        bool empty() const { return size() == 0; }
    };
    AdjacencyRange operator[](std::size_t i) const {
        return AdjacencyRange{data.begin() + index[i], data.begin() + index[i + 1]};
    }

    void build() {
        std::partial_sum(index.begin(), index.end(), index.begin());
        data.resize(_m);
        for (auto&& e : buf) data[--index[e.src]] = e;
        _build_flg = true;
    }
    void add_edge(const Edge& e) {
        ++index[e.src];
        buf.emplace_back(e);
        if (buf.size() == _m) build();
    }
    void add_edge(std::size_t src, std::size_t dest, ll weight = 1) { add_edge(Edge(src, dest, weight)); }
    std::size_t size() const { return _n; }
    std::size_t n_edge() const { return _m; }
    bool build_flg() const { return _build_flg; }

   private:
    std::size_t _n, _m;
    std::vector<Edge> buf, data;
    std::vector<std::size_t> index;
    bool _build_flg;
};
}  // namespace bys
namespace bys {
/**
 * @brief Single Source Shortest Path Result
 * 単一始点最短経路問題の答え
 * 経路復元もできる
 */
struct SSSPResult {
    std::size_t source;
    std::vector<ll> cost;
    std::vector<int> prev;

    SSSPResult(std::size_t _n, std::size_t _source) : source(_source), cost(_n, LINF), prev(_n, -1) {}
    vector<std::size_t> path(int to) const {
        vector<std::size_t> res;
        while (to != -1) {
            res.push_back(to);
            to = prev[to];
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
struct APSPResult {
    std::vector<std::vector<ll>> cost;
    std::vector<std::vector<int>> prev;
    APSPResult(std::size_t _n) : cost(_n, vector(_n, LINF)), prev(_n, vector(_n, -1)) {}
    std::vector<std::size_t> path(int from, int to) {
        vector<std::size_t> res;
        for (int now = to; now != from; now = prev[from][now]) {
            res.push_back(now);
        }
        res.push_back(from);
        std::reverse(res.begin(), res.end());
        return res;
    }
};
}  // namespace bys
namespace bys {
/**
 * @brief 幅優先探索
 *
 * @tparam AdjacencyList or DynamicAdjacencyList
 */
template <class Adj>
SSSPResult breadth_first_search(const Adj& graph, std::size_t source) {
    std::size_t n = graph.size();
    SSSPResult res(n, source);
    std::queue<std::size_t> que;
    que.emplace(source);
    res.cost[source] = 0;
    while (!que.empty()) {
        auto top = que.front();
        que.pop();
        for (auto&& next : graph[top]) {
            if (res.cost[next] == LINF) {
                res.prev[next] = top;
                res.cost[next] = res.cost[top] + 1;
                que.emplace(next.dest);
            }
        }
    }
    return res;
}
SSSPResult zero_one_bfs(const AdjacencyList& graph, std::size_t source) {
    std::size_t n = graph.size();
    SSSPResult res(n, source);
    std::deque<std::size_t> que;
    que.emplace_back(source);
    res.cost[source] = 0;
    while (!que.empty()) {
        auto top = que.front();
        que.pop_front();
        for (auto&& next : graph[top]) {
            ll next_cost = res.cost[top] + next.weight;
            if (next_cost >= res.cost[next]) continue;
            res.cost[next] = next_cost;
            res.prev[next] = top;
            if (next.weight == 0) {
                que.emplace_front(next.dest);
            } else if (next.weight == 1) {
                que.emplace_back(next.dest);
            } else {
                throw RE;
            }
        }
    }
    return res;
}

}  // namespace bys

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
constexpr T mod_pow(T p, T q, T mod) {
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
template <class T, class S>
constexpr T floormod(T x, S mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
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
//! @brief グリッド探索管理
struct Grid {
    int h, w;
    Grid(int row, int col) : h(row), w(col) {}

    bool contain(int row, int col) const { return 0 <= row && row < h && 0 <= col && col < w; }
    int area() const { return h * w; }
    int index(int row, int col) const {
        assert(contain(row, col));
        return row * w + col;
    }
    int index(std::pair<int, int> p) const { return index(p.first, p.second); }

    pair<int, int> coord(int idx) const {
        assert(0 <= idx && idx < area());
        return {idx / w, idx % w};
    }
    vector<pair<int, int>> next(int row, int col, const vector<pair<int, int>> delta) const {
        assert(contain(row, col));
        vector<pair<int, int>> res;
        for (auto [di, dj] : delta) {
            int ni = row + di;
            int nj = col + dj;
            if (contain(ni, nj)) res.push_back({ni, nj});
        }
        return res;
    }
    //! @brief 右・下
    vector<pair<int, int>> next2(int row, int col) const { return next(row, col, {{1, 0}, {0, 1}}); }
    //! @brief 上下左右
    vector<pair<int, int>> next4(int row, int col) const { return next(row, col, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}); }
    //! @brief 8方向
    vector<pair<int, int>> next8(int row, int col) const {
        vector<pair<int, int>> delta;
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                delta.push_back({di, dj});
            }
        }
        return next(row, col, delta);
    }
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
/*
初期解を生成

適当に変えつつシミュレーション

最も到達確率が高いものを探す
*/
namespace bys {
void Solver::solve() {
    Timer timer(1950);
    constexpr int M = 20;
    constexpr int SIZE = 200;
    constexpr int REP = 10000;
    constexpr std::size_t bits = std::numeric_limits<float>::digits;
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    string dir = "RLUDRRRDDDUULLD";
    const int dirsize = dir.length();
    std::uniform_int_distribution<> dist(0, SIZE * dirsize - 1);

    // 入力
    auto [si, sj, ti, tj] = scanner.read<int, 4>();
    auto p = scanner.read<float>();
    auto h = scanner.readvec<string>(M);
    auto v = scanner.readvec<string>(M - 1);

    // 前処理
    DynamicAdjacencyList graph(M * M);
    Grid grid(M, M);
    int s = grid.index(si, sj);
    int t = grid.index(ti, tj);
    Pa g = {ti, tj};
    for (int i : irange(M)) {
        for (int j : irange(M - 1)) {
            if (h[i][j] == '0') {
                graph.add_edge(grid.index(i, j), grid.index(i, j + 1));
                graph.add_edge(grid.index(i, j + 1), grid.index(i, j));
            }
        }
    }
    for (int i : irange(M - 1)) {
        for (int j : irange(M)) {
            if (v[i][j] == '0') {
                graph.add_edge(grid.index(i, j), grid.index(i + 1, j));
                graph.add_edge(grid.index(i + 1, j), grid.index(i, j));
            }
        }
    }
    auto bounds_check = [&](int p) -> bool { return 0 <= p and p < M - 1; };

    // 初期解生成
    string com, ans;
    {
        auto res = breadth_first_search(graph, s);
        auto path = res.path(t);
        for (int i : irange(path.size() - 1)) {
            int diff = path[i + 1] - path[i];
            if (diff == 1) {
                com.push_back('R');
            } else if (diff == -1) {
                com.push_back('L');
            } else if (diff == M) {
                com.push_back('D');
            } else if (diff == -M) {
                com.push_back('U');
            } else {
                throw RE;
            }
            float rand = std::generate_canonical<float, bits>(engine);
            if (rand < p + 0.2) com.push_back(com.back());
        }
        while ((int)com.length() < SIZE) {
            int rnd = dist(engine);
            int mod = rnd % dirsize;
            com.push_back(dir[mod]);
        }
        ans = com;
    }
    // DEBUG(com);
    assert((int)com.length() == SIZE);

    int cnt = -1;
    int imp = 0;
    while (timer.counting()) {
        int rnd = dist(engine);
        int div = rnd / dirsize;
        int mod = rnd % dirsize;
        char prev = com[div];
        com[div] = dir[mod];

        int succsess = 0;
        Pa now = {si, sj};
        for (UV : irange(REP)) {
            for (auto ci : com) {
                float rand = std::generate_canonical<float, bits>(engine);
                if (rand < p) continue;
                if (ci == 'L') {
                    if (bounds_check(now.second - 1) and h[now.first][now.second - 1] == '0') {
                        --now.second;
                    }
                } else if (ci == 'R') {
                    if (bounds_check(now.second) and h[now.first][now.second] == '0') {
                        ++now.second;
                    }
                } else if (ci == 'U') {
                    if (bounds_check(now.first - 1) and v[now.first - 1][now.second] == '0') {
                        --now.first;
                    }
                } else if (ci == 'D') {
                    if (bounds_check(now.first) and v[now.first][now.second] == '0') {
                        ++now.first;
                    }
                } else {
                    throw RE;
                }
                if (now == g) {
                    ++succsess;
                    break;
                }
            }
        }
        if (chmax(cnt, succsess)) {
            ++imp;
            ans = com;
        } else {
            com[div] = prev;
        }
    }
    DEBUG(cnt, imp);
    print(ans);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
