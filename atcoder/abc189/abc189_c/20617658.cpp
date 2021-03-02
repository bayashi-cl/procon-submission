#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    int ans = 0;
    for (auto&& i : A) {
        cin >> i;
    }
    for (auto&& i : irange(N)) {
        int mina = INF;
        for (auto&& j : irange(N - i)) {
            mina = min(mina, A[i + j]);
            ans = max(ans, mina * (j + 1));
        }
    }
    cout << ans << endl;
}