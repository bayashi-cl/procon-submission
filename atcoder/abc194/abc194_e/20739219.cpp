#include <bits/stdc++.h>
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

using ll = long long;
using P = pair<ll, ll>;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (auto&& i : A) cin >> i;
    vector<int> count(N + 1);
    for (int i : irange(M)) count[A[i]]++;
    int now = 0;
    while (count[now]) now++;
    int mex = now;
    for (int i = 0; i < N - M; i++) {
        count[A[i]]--;
        count[A[i + M]]++;
        if (count[A[i]] == 0 && A[i] < now) now = A[i];
        mex = min(mex, now);
    }
    cout << mex << endl;
    return 0;
}
