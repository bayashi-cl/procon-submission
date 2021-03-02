#include <bits/stdc++.h>
using ll = long long;
using namespace std;

#include <boost/range/irange.hpp>
using boost::irange;

#include <atcoder/maxflow>

const int INF = (1 << 30) - 1;
const int MOD = 1e9 + 7;
const ll LINF = 1LL << 60;

int main() {
    int N;
    cin >> N;
    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        cin >> board[i];
        for (int j = 0; j < N; j++) {
            if ((i + j) % 2 == 1) {
                if (board[i][j] == 'B')
                    board[i][j] = 'W';
                else if (board[i][j] == 'W')
                    board[i][j] = 'B';
            }
        }
    }

    int s = N * N, t = s + 1;
    atcoder::mf_graph<int> graph(s + 2);
    for (int i:irange(N)) {
        for (int j : irange(N)) {
            int index = N * i + j;
            if (board[i][j] == 'W') {
                graph.add_edge(s, index, INF);
            }
            if (board[i][j] == 'B') {
                graph.add_edge(index, t, INF);
            }

            if (i > 0) {
                int up_index = N * (i - 1) + j;
                graph.add_edge(up_index, index, 1);
                graph.add_edge(index, up_index, 1);
            }
            if (j > 0) {
                int left_index = N * i + (j - 1);
                graph.add_edge(left_index, index, 1);
                graph.add_edge(index, left_index, 1);
            }
        }
    }
    int min_cut = graph.flow(s, t);
    cout << 2 * N * (N - 1) - min_cut << endl;
    return 0;
}