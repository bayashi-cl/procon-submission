#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <atcoder/segtree>

using Sorted = std::tuple<bool, int, int>;  // {sorted, min, max}
Sorted op_sorted(const Sorted a, const Sorted b) {
    auto [a_sorted, a_min, a_max] = a;
    auto [b_sorted, b_min, b_max] = b;
    auto sorted = a_sorted & b_sorted & (a_max <= b_min);
    return {sorted, std::min(a_min, b_min), std::max(a_max, b_max)};
}
Sorted e_sorted() { return {true, std::numeric_limits<int>::max(), std::numeric_limits<int>::min()}; }
Sorted to_sorted(int v) { return {true, v, v}; }

using Count = std::array<int, 26>;
Count op_count(const Count a, const Count b) {
    Count result;
    for (auto i = 0; i < 26; ++i) result[i] = a[i] + b[i];
    return result;
}
Count e_count() {
    Count result;
    result.fill(0);
    return result;
}
Count to_count(char v) {
    auto result = e_count();
    ++result[v];
    return result;
}

int main() {
    int n, q;
    std::string s_char;
    std::cin >> n >> s_char >> q;
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) s[i] = s_char[i] - 'a';

    std::vector<Sorted> v_sorted(n);
    std::vector<Count> v_count(n);

    for (int i = 0; i < n; ++i) {
        v_sorted[i] = to_sorted(s[i]);
        v_count[i] = to_count(s[i]);
    }

    atcoder::segtree<Sorted, op_sorted, e_sorted> seg_sorted(v_sorted);
    atcoder::segtree<Count, op_count, e_count> seg_count(v_count);

    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int x;
            char c_char;
            std::cin >> x >> c_char;
            --x;
            int c = c_char - 'a';

            seg_sorted.set(x, to_sorted(c));
            seg_count.set(x, to_count(c));
        } else if (t == 2) {
            int l, r;
            std::cin >> l >> r;
            --l;

            auto [sorted, min, max] = seg_sorted.prod(l, r);
            if (sorted) {
                auto sub_count = seg_count.prod(l, r);
                auto s_count = seg_count.all_prod();

                bool ans = true;
                for (auto i = min + 1; i < max; ++i) {
                    if (s_count[i] != sub_count[i]) {
                        ans = false;
                    }
                }
                std::cout << (ans ? "Yes" : "No") << '\n';
            } else {
                std::cout << "No\n";
            }
        }
    }
}
