#include <atcoder/math>
#include <atcoder/modint>
#include <boost/range/irange.hpp>
#include <cmath>
#include <ctime>
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
using atcoder::pow_mod, atcoder::inv_mod;
using boost::irange;
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort, std::abs, std::pow;
using std::vector, std::string, std::set, std::map, std::pair;
using mint = atcoder::modint1000000007;
using ll = long long int;
using Pa = std::pair<int, int>;
using Vec = std::vector<int>;
using VecVec = std::vector<Vec>;
constexpr int MOD = 1000000007;
constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr ll LINF = std::numeric_limits<ll>::max() / 2;
// clang-format off
inline std::istream& operator>>(std::istream& is, mint& m) {ll n; is >> n; m = n; return is;}
inline std::ostream& operator<<(std::ostream& os, const mint& m) { os << m.val(); return os;}
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
struct Station {
    int right, left;
};
void solve() {
    int ti = clock();
    int M, S, T, L;
    cin >> M >> S >> T >> L;
    vector<vector<int> > t(M, vector<int>(S));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < S; j++) {
            cin >> t[i][j];
        }
    }
    int tmp = 0;
    vector<Station> station(S);
    for (int i = 0; i < S; i++) {
        int x;
        cin >> x;
        station[i].left = tmp + 1;
        station[i].right = x;
        tmp = x;
    }
    int N = 0;
    vector<int> num(M);
    for (int i = 0; i < M; i++) {
        cin >> num[i];
        N += num[i];
    }

    auto calc = [&](int K, vector<int>& p) {
        //シミュレーション

        int Time = 0;
        int stop_Time = 0;

        //各ステーションに対し、次に処理すべきタスクの番号(0~K-1)
        vector<int> head(S);

        //タスクとステーションのペアに関する進捗
        vector<vector<int> > progress(K, vector<int>(S));

        //各種類のタスクについて完了した個数
        vector<int> m(M);

        while (head[S - 1] < K) {
            //以下の中の最短時間を求める
            //未完了のタスクが未完了のままステーションの終点につく時間
            //あるタスクについて次のステーションに到着する時間
            //タスク完了する時間
            int t_min = INF;

            for (int j = 0; j < S; j++) {
                int k = head[j];
                if (k == K) continue;
                int x = Time - stop_Time - k * T;
                if (x < station[j].left) {
                    t_min = min(t_min, station[j].left - x);
                } else {
                    t_min = min(t_min, min(station[j].right - x,
                                           t[p[k]][j] - progress[k][j]));
                }
            }
            //次のイベントが L を超えているなら終了
            if (t_min + Time > L) {
                Time = L + 1;
                break;
            }
            //そうでない時、次のイベントを処理して時間計算
            if (t_min > 0) {
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    if (x >= station[j].left) progress[k][j] += t_min;
                }
                Time += t_min;
            } else {
                int res_min = INF;
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    res_min = min(res_min, t[p[k]][j] - progress[k][j]);
                }

                if (res_min + Time > L) {
                    Time = L + 1;
                    break;
                }
                stop_Time += res_min;
                Time += res_min;
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    progress[k][j] += res_min;
                    if (progress[k][j] == t[p[k]][j]) {
                        head[j]++;
                        if (j == S - 1) {
                            m[p[k]]++;
                        }
                    }
                }
            }
        }
        //スコア計算
        int score = 0;
        if (Time == L + 1 || K < N) {
            double sc = 0;
            for (int i = 0; i < M; i++) {
                sc += sqrt((double)m[i] / (double)num[i]);
            }
            sc *= 1000000.0;
            sc /= M;
            score = round(sc);
        } else {
            double sc = 1000000.0 * (2.0 - (double)Time / (double)L);
            score = round(sc);
        }
        return score;
    };

    Vec plan, ans;
    for (int i = 0; i < M; ++i) {
        for (int k = 0; k < num[i]; ++k) {
            plan.push_back(i);
        }
    }
    int score = 0;
    do {
        if (clock() - ti > 190 * CLOCKS_PER_SEC / 100) break;
        if (chmax(score, calc(plan.size(), plan))) ans = plan;
    } while (std::next_permutation(std::begin(plan), std::end(plan)));

    print(ans.size());
    for (auto&& ai : ans) ai++;
    print(ans);
}
}  // namespace bys

int main() {
    bys::init();
    bys::solve();
    std::cout << std::flush;
    return 0;
}
