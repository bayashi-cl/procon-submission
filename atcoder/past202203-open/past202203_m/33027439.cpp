#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include <utility>
#include <vector>

namespace pbds = __gnu_pbds;
template <class T, class Comp>
using Tree = pbds::tree<T, pbds::null_type, Comp, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;
template <class T>
using OrderdSetGt = Tree<T, std::greater<T>>;
using std::cin, std::cout;

int main() {
    int N, Q;
    cin >> N >> Q;
    std::vector<int> p(N);
    OrderdSetGt<std::pair<int, int>> s;

    for (auto i = 0; i < N; ++i) {
        cin >> p[i];
        s.insert({p[i], i});
    }

    for (auto q = 0; q < Q; ++q) {
        int t;
        cin >> t;
        switch (t) {
            case 1: {
                int a, x;
                cin >> a >> x;
                --a;
                s.erase({p[a], a});
                s.insert({x, a});
                p[a] = x;
            } break;
            case 2: {
                int a;
                cin >> a;
                --a;
                cout << s.order_of_key({p[a], a}) + 1 << '\n';
            } break;
            case 3: {
                int r;
                cin >> r;
                cout << s.find_by_order(r - 1)->second + 1 << '\n';
            } break;
        }
    }
    cout << std::flush;
}
