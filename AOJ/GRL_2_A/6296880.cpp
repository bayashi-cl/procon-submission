#line 1 "test/graph/kruskal.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_2_A"
#line 2 "core/stdlib.hpp"
#ifndef LOCAL
#define NDEBUG
#endif

#include <algorithm>
#include <array>
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
#line 3 "core/const.hpp"

namespace bys {
constexpr int MOD = 998244353;
constexpr int MOD7 = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
}  // namespace bys
#line 4 "core/types.hpp"
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
#line 4 "core/printer.hpp"

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
#line 4 "core/scanner.hpp"

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
#line 5 "core/io.hpp"

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
#line 2 "core/macro.hpp"
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
#define RE std::runtime_error("line: " + std::to_string(__LINE__) + ", func: " + __func__)
// clang-format on
#line 2 "core/solver.hpp"

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
#line 3 "data/union_find.hpp"
namespace bys {
struct UnionFindTree {
    UnionFindTree() : _n(0) {}
    UnionFindTree(std::size_t n) : _n(n), _n_tree(_n), parent(_n, -1) {}

    std::size_t find(std::size_t a) {
        assert(a < _n);
        std::vector<std::size_t> path;
        while (parent[a] >= 0) {
            path.emplace_back(a);
            a = parent[a];
        }
        for (auto&& p : path) parent[p] = a;
        return a;
    }
    bool same(std::size_t a, std::size_t b) {
        assert(a < _n);
        assert(b < _n);
        return find(a) == find(b);
    }
    bool unite(std::size_t a, std::size_t b) {
        assert(a < _n);
        assert(b < _n);
        a = find(a);
        b = find(b);
        if (a == b) return false;
        --_n_tree;
        if (-parent[a] < -parent[b]) std::swap(a, b);
        parent[a] += parent[b];
        parent[b] = a;
        return true;
    }
    std::map<std::size_t, std::vector<std::size_t>> groups() {
        std::map<std::size_t, std::vector<std::size_t>> res;
        for (std::size_t i = 0; i < _n; ++i) res[find(i)].emplace_back(i);
        return res;
    };
    std::size_t size(std::size_t a) { return -parent[find(a)]; }
    std::size_t n_tree() { return _n_tree; }

   private:
    std::size_t _n, _n_tree;
    std::vector<int> parent;  // 負なら親でありその値は(-子の数)
};
}  // namespace bys
#line 3 "graph/edge.hpp"

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
    operator std::size_t() const { return to; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        return os << "{" << e.from << " -> " << e.to << ": " << e.cost << "}";
    }
};
using Adj = vector<vector<Edge>>;
using EdgeList = vector<Edge>;
}  // namespace bys
#line 5 "graph/kruskal.hpp"

namespace bys {
struct Kruskal {
    int n_node;
    EdgeList mst;
    ll cost = 0;
    Kruskal(EdgeList& edges, int n_node, int n_tree = 1) : n_node(n_node) {
        sort(edges.begin(), edges.end());
        search(edges, n_tree);
    }
    void search(const EdgeList& edges, int n_tree) {
        UnionFindTree uft(n_node);
        int sz = n_node;
        for (auto&& e : edges) {
            if (uft.same(e.from, e.to)) continue;
            uft.unite(e.from, e.to);
            mst.push_back(e);
            cost += e.cost;
            --sz;
            if (sz == n_tree) return;
        }
    }
};
}  // namespace bys
#line 4 "test/graph/kruskal.test.cpp"

namespace bys {
void Solver::solve() {
    auto [v, e] = scanner.read<int, 2>();
    EdgeList elist;
    for (int i = 0; i < e; ++i) {
        auto [s, t, w] = scanner.read<int, 3>();
        elist.push_back({s, t, w});
    }
    Kruskal kru(elist, v);
    print(kru.cost);
}
}  // namespace bys

int main() {
    bys::Solver solver;
    solver.solve(/* bys::scanner.read<int>() */);
    return 0;
}

