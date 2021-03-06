#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> tree;
    vector<int> rank;
    UnionFind(int n) : tree(n, -1), rank(n, 1) {}
    int find(int x) {
        if (tree[x] == -1)
            return x;
        else
            return tree[x] = find(tree[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] > rank[y]) swap(x, y);
        if (rank[x] == rank[y]) rank[y]++;
        tree[x] = y;
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    UnionFind uf(N);
    for (int q = 0; q < Q; q++) {
        int P, A, B;
        cin >> P >> A >> B;
        if (P == 0) {
            uf.unite(A, B);
        }
        if (P == 1) {
            if (uf.find(A) == uf.find(B)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
