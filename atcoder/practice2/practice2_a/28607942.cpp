#include <atcoder/dsu>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    atcoder::dsu uft(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) {
            uft.merge(u, v);
        } else {
            if (uft.same(u, v)) {
                std::cout << 1 << '\n';
            } else {
                std::cout << 0 << '\n';
            }
        }
    }
    std::cout << std::flush;
    return 0;
}
