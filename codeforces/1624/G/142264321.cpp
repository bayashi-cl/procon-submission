#line 1 "/home/bayashi/git/ac-library/atcoder/dsu.hpp"



#include <algorithm>
#include <cassert>
#include <vector>

namespace atcoder {

// Implement (union by size) + (path compression)
// Reference:
// Zvi Galil and Giuseppe F. Italiano,
// Data structures and algorithms for disjoint set union problems
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    std::vector<int> parent_or_size;
};

}  // namespace atcoder


#line 2 "/home/bayashi/dev/byslib/core/stdlib.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#line 7 "/home/bayashi/dev/byslib/core/stdlib.hpp"
#include <array>
#line 9 "/home/bayashi/dev/byslib/core/stdlib.hpp"
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
#line 25 "/home/bayashi/dev/byslib/core/stdlib.hpp"

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
#line 3 "/home/bayashi/dev/byslib/graph/edge.hpp"

namespace bys {
struct Edge {
    int from, to;
    ll cost;

    //! @brief 重みなし単頂点
    Edge(int to) : from(-1), to(to), cost(1) {}
    //! @brief 重み付き単頂点
    Edge(int to, ll cost) : from(-1), to(to), cost(cost) {}
    //! @brief 重み付き両頂点
    Edge(int from, int to, ll cost) : from(from), to(to), cost(cost) {}
    bool operator<(const Edge& rh) const { return cost < rh.cost; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) { return os << e.from << " - " << e.to << ": " << e.cost; }
};
using Adj = vector<vector<Edge>>;
using EdgeList = vector<Edge>;
}  // namespace bys
#line 5 "/home/bayashi/dev/byslib/graph/reader.hpp"

namespace bys {
Adj read_adj_uv(int n, int m, bool directed = false, int index = 1) {
    Adj graph(n);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = input<int, 2>();
        u -= index;
        v -= index;
        graph[u].push_back({v});
        if (!directed) graph[v].push_back({u});
    }
    return graph;
}
Adj read_adj_uvc(int n, int m, bool directed = false, int index = 1) {
    Adj graph(n);
    for (int i = 0; i < m; ++i) {
        auto [u, v, c] = input<int, int, ll>();
        u -= index;
        v -= index;
        graph[u].push_back({v, c});
        if (!directed) graph[v].push_back({u, c});
    }
    return graph;
}
EdgeList read_elist_uv(int m, int index = 1) {
    EdgeList elist;
    elist.reserve(m);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = input<int, 2>();
        u -= index;
        v -= index;
        elist.push_back({u, v, 1});
    }
    return elist;
}
EdgeList read_elist_uvc(int m, int index = 1) {
    EdgeList elist;
    elist.reserve(m);
    for (int i = 0; i < m; ++i) {
        auto [u, v, c] = input<int, int, ll>();
        u -= index;
        v -= index;
        elist.push_back({u, v, c});
    }
    return elist;
}
}  // namespace bys
#line 3 "/home/bayashi/dev/byslib/math/bit.hpp"

namespace bys {
int bit_length(ll x) {
    int bits = 0;
    x = (x < 0) ? (-x) : x;
    for (bits = 0; x != 0; bits++) x >>= 1;
    return bits;
}
inline bool pop(int s, int d) { return s & (1 << d); }
inline bool pop(ll s, int d) { return s & (1LL << d); }
}  // namespace bys
#line 2 "/home/bayashi/dev/byslib/utility/change.hpp"
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
#line 7 "G/main.cpp"

namespace bys {
void Solver::solve() {
    auto [n, m] = input<int, 2>();
    auto graph = read_elist_uvc(m);

    set<int> removed;
    int ans = 0;
    for (int d : reversed(Range(32))) {
        set<int> remove_cand;
        atcoder::dsu uft(n);
        for (int i : Range(m)) {
            if (removed.find(i) != removed.end()) continue;
            auto&& e = graph[i];
            if (pop(e.cost, d)) {
                remove_cand.insert(i);
            } else {
                uft.merge(e.from, e.to);
            }
        }
        if (uft.size(0) == n) {
            for (auto&& r : remove_cand) removed.insert(r);
        } else {
            ans ^= (1 << d);
        }
    }
    print(ans);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(bys::input<int>());
    return 0;
}
