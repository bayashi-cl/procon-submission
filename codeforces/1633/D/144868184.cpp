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
using ibool = std::int8_t;
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
#line 4 "/home/bayashi/dev/byslib/core/types.hpp"
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
#line 4 "/home/bayashi/dev/byslib/core/printer.hpp"

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
#line 4 "/home/bayashi/dev/byslib/core/scanner.hpp"

namespace bys {
struct Scanner {
    Scanner(std::istream& is_) : is(is_){};

    template <class... Ts>
    void scan(Ts&... args) {
        is_read_from_istream = true;
        (is >> ... >> args);
    }

    template <class T, class... Us>
    decltype(auto) read() {
        is_read_from_istream = true;
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
        std::string elem;
        if (is_read_from_istream) std::getline(is, elem);
        if (!elem.empty()) std::cerr << "\e[33mWarnig!!\e[0m Some inputs were ignored." << std::endl;
        std::getline(is, elem);
        std::stringstream ss{elem};
        std::vector<T> res;
        while (std::getline(ss, elem, sep)) res.emplace_back(f(elem));
        return res;
    }

   private:
    std::istream& is;
    bool is_read_from_istream = false;
    template <class Tp, std::size_t... I>
    inline decltype(auto) read_tuple(std::index_sequence<I...>) {
        return Tp{read<typename std::tuple_element_t<I, Tp>>()...};
    }
};
}  // namespace bys
#line 5 "/home/bayashi/dev/byslib/core/io.hpp"

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
#line 2 "/home/bayashi/dev/byslib/core/macro.hpp"
// clang-format off
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
// clang-format on
#line 2 "/home/bayashi/dev/byslib/core/solver.hpp"

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
#line 5 "/home/bayashi/dev/byslib/graph/breadth_first.hpp"

namespace bys {
struct BreadthFirstSearch {
    int n_node;
    vector<int> prev;
    vector<int> cost;

    BreadthFirstSearch(const Adj& graph, int start, int err_val = -1)
        : n_node(graph.size()), prev(n_node, -1), cost(n_node, INF) {
        search(graph, start);
        std::replace(cost.begin(), cost.end(), INF, err_val);
    }

    void search(const Adj& graph, int start) {
        cost[start] = 0;
        std::queue<int> que;
        que.push(start);
        while (!que.empty()) {
            int from = que.front();
            que.pop();
            for (auto&& to : graph[from]) {
                if (cost[to.to] == INF) {
                    prev[to.to] = from;
                    cost[to.to] = cost[from] + 1;
                    que.push(to.to);
                }
            }
        }
    }
    vector<int> path(int to) {
        assert(to < n_node);
        vector<int> res;
        while (to != -1) {
            res.push_back(to);
            to = prev[to];
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
struct ZeroOneBFS {
    int n_node;
    vector<int> cost;
    vector<int> prev;

    ZeroOneBFS(Adj& graph, int start, int err_val = -1) : n_node(graph.size()), cost(n_node, INF), prev(n_node, -1) {
        search(graph, start);
        std::replace(cost.begin(), cost.end(), INF, err_val);
    }

    void search(const Adj& graph, int start) {
        std::deque<int> que;
        cost[start] = 0;
        que.push_back(start);
        while (!que.empty()) {
            int now = que.front();
            que.pop_front();
            for (auto&& to : graph[now]) {
                int dist = cost[now] + to.cost;
                if (dist >= cost[to.to]) continue;
                cost[to.to] = dist;
                prev[to.to] = now;
                if (to.cost == 0) {
                    que.push_front(to.to);
                } else {
                    que.push_back(to.to);
                }
            }
        }
    }
    vector<int> path(int to) {
        assert(to < n_node);
        vector<int> res;
        while (to != -1) {
            res.push_back(to);
            to = prev[to];
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};
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
#line 5 "D/main.cpp"

namespace bys {
void Solver::solve() {
    auto t = scanner.read<int>();
    int mx = 1001;
    Adj graph(mx);
    for (int i : Range(1, mx)) {
        for (auto&& x : Range(1, i + 1)) {
            if (int to = i + i / x; to < mx) {
                graph[i].push_back(to);
            }
        }
    }
    BreadthFirstSearch bfs(graph, 1);

    for (UV : Range(t)) {
        auto [n, k] = scanner.read<int, 2>();
        auto b = scanner.readvec<int>(n);
        auto c = scanner.readvec<int>(n);
        for (auto&& bi : b) bi = bfs.cost[bi];

        // vector dp(n + 1, map<int, int>());
        // dp[0][0] = 0;

        // for (int i : Range(n)) {
        //     for (auto&& [key, val] : dp[i]) {
        //         chmax(dp[i + 1][key], val);
        //         if (int nxt = key + b[i]; nxt <= k) chmax(dp[i + 1][nxt], val + c[i]);
        //     }
        // }

        // int ans = 0;
        // for (auto&& [key, val] : dp[n]) chmax(ans, val);
        // print(ans);

        map<int, int> dp, dp_nxt;
        dp[0] = 0;
        for (int i : Range(n)) {
            dp_nxt.clear();
            for (auto&& [key, val] : dp) {
                chmax(dp_nxt[key], val);
                if (int nxt = key + b[i]; nxt <= k) chmax(dp_nxt[nxt], val + c[i]);
            }
            dp = dp_nxt;
        }
        int ans = 0;
        for (auto&& [key, val] : dp) chmax(ans, val);
        print(ans);
    }
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}
