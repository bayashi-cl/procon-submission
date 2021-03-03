#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// #include <boost/range/irange.hpp>
// using boost::irange;
// #include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
namespace ublas = boost::numeric::ublas;

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N;
    cin >> N;
    vector<ublas::vector<ll>> piece;
    for (int i = 0; i < N; i++) {
        ll x, y;
        cin >> x >> y;
        ublas::vector<ll> v(3);
        v[0] = x;
        v[1] = y;
        v[2] = 1;
        piece.push_back(v);
    }

    vector<ublas::matrix<ll>> history;
    history.push_back(ublas::identity_matrix<ll>(3, 3));
    ublas::matrix<ll> op1(ublas::zero_matrix<ll>(3, 3));
    op1(0, 1) = 1;
    op1(1, 0) = -1;
    op1(2, 2) = 1;
    ublas::matrix<ll> op2(ublas::zero_matrix<ll>(3, 3));
    op2(0, 1) = -1;
    op2(1, 0) = 1;
    op2(2, 2) = 1;
    ublas::matrix<ll> op3(ublas::zero_matrix<ll>(3, 3));
    op3(0, 0) = -1;
    op3(1, 1) = 1;
    op3(2, 2) = 1;
    ublas::matrix<ll> op4(ublas::zero_matrix<ll>(3, 3));
    op4(0, 0) = 1;
    op4(1, 1) = -1;
    op4(2, 2) = 1;

    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            history.push_back(ublas::prod(op1, history[i]));
        } else if (op == 2) {
            history.push_back(ublas::prod(op2, history[i]));
        } else if (op == 3) {
            ll p;
            cin >> p;
            op3(0, 2) = 2 * p;
            history.push_back(ublas::prod(op3, history[i]));
        } else if (op == 4) {
            ll p;
            cin >> p;
            op4(1, 2) = 2 * p;
            history.push_back(ublas::prod(op4, history[i]));
        } else {
            cout << "error" << endl;
            return 0;
        }
    }

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int A, B;
        cin >> A >> B;
        ublas::vector<ll> ans = ublas::prod(history[A], piece[B - 1]);
        cout << ans[0] << " " << ans[1] << endl;
    }
}