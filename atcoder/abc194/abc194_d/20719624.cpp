#include <bits/stdc++.h>
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;

using ll = long long;
using P = pair<ll, ll>;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    double N;
    cin >> N;
    double ans;
    for (int i = 1; i < N; i++) ans += N / i;
    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}
