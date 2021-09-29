#include <cmath>
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
#include <valarray>
#include <vector>

namespace bys {
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
template <class T> std::istream& operator>>(std::istream& is, vector<T>& vec) {for (auto&& v : vec) is >> v; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {for (std::size_t i = 0; i < vec.size(); i++) {if (i) os << " "; os << vec[i];} return os;}
template <class T> std::istream& operator>>(std::istream& is, std::valarray<T>& arr) {for (auto&& a : arr) is >> a; return is;}
template <class T> std::ostream& operator<<(std::ostream& os, const std::valarray<T>& arr) {for (std::size_t i = 0; i < arr.size(); i++) {if (i) os << " "; os << arr[i];} return os;}
template <class S, class T> std::istream& operator>>(std::istream& is, std::pair<S, T>& p) {is >> p.first >> p.second; return is;}
template <class S, class T> std::ostream& operator<<(std::ostream& os, const std::pair<S, T>& p) {os << p.first << " " << p.second; return os;}
template <class T> inline T input() {T n; cin >> n; return n;}
template <class T> inline vector<T> input(int n) {vector<T> res(n); for (auto&& r : res) cin >> r; return res;}
template <class T, size_t N> inline std::array<T, N> input() {std::array<T, N> res; for (auto&& r : res) cin >> r; return res;}
template <class Tail> void print(Tail&& tail) {cout << tail << "\n";}
template <class Head, class... Body> void print(Head&& head, Body&&... tail) {cout << head << " "; print(std::forward<Body>(tail)...);}
template <class Tail> void debug(Tail&& tail) {std::clog << tail << endl;}
template <class Head, class... Body> void debug(Head&& head, Body&&... tail) {std::clog << head << " "; debug(std::forward<Body>(tail)...);}
template <class T> inline bool chmax(T& a, const T& b) {if (a < b) {a = b; return 1;} return 0;}
template <class T> inline bool chmin(T& a, const T& b) {if (b < a) {a = b; return 1;} return 0;}
void init() {cin.tie(nullptr); std::ios::sync_with_stdio(false); cout << std::fixed << std::setprecision(11) << std::boolalpha;}
// clang-format on
}  // namespace bys

namespace bys {
using Card = pair<int, char>;
vector<Card> bubble_sort(vector<Card> v) {
    int n = v.size();
    bool flg = true;
    while (flg) {
        flg = false;
        for (int j = n - 1; j > 0; --j) {
            if (v[j].first < v[j - 1].first) {
                std::swap(v[j], v[j - 1]);
                flg = true;
            }
        }
    }
    return v;
}
vector<Card> selection_sort(vector<Card> v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        int mini = i;
        for (int j = i; j < n; ++j) {
            if (v[j].first < v[mini].first) mini = j;
        }
        std::swap(v[i], v[mini]);
    }
    return v;
}
void print_hand(vector<Card> h) {
    int n = h.size();
    for (int i = 0; i < n - 1; ++i) {
        cout << h[i].second << h[i].first << ' ';
    }
    cout << h[n - 1].second << h[n - 1].first << endl;
}

void solve() {
    auto n = input<int>();
    auto a = input<string>(n);
    vector<Card> hand;
    for (auto&& e : a) hand.push_back({e[1] - '0', e[0]});

    auto bub = bubble_sort(hand);
    auto sel = selection_sort(hand);

    print_hand(bub);
    print("Stable");
    print_hand(sel);
    print((bub == sel) ? "Stable" : "Not stable");
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}

