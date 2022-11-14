#include <cstddef>
#include <iostream>
#include <map>
#include <tuple>
#include <type_traits>
#include <utility>

template <class F>
class Cache {
    template <class>
    struct get_signature {};

    template <class Fn, class R, class FnRef, class... Args>
    struct get_signature<R (Fn::*)(FnRef, Args...) const> {
        using result_type = R;
        using args_tuple = std::tuple<std::decay_t<Args>...>;
    };

    using signature = get_signature<decltype(&F::template operator()<Cache<F> &>)>;
    using args_tuple = typename signature::args_tuple;
    using result_type = typename signature::result_type;

    F func;
    std::map<args_tuple, result_type> memo;

   public:
    Cache(F const &fn) : func(fn) {}

    template <class... Args>
    result_type operator()(Args &&...args) {
        args_tuple key{std::forward<Args>(args)...};
        if (auto itr = memo.find(key); itr == memo.end()) {
            result_type res = func(*this, std::forward<Args>(args)...);
            memo.emplace(key, res);
            return res;
        } else {
            return itr->second;
        }
    }
};

using ll = std::int64_t;
int main() {
    ll N;
    std::cin >> N;

    Cache f([](auto &&f, ll x) -> ll {
        if (x == 0) {
            return 1;
        } else {
            return f(x / 2) + f(x / 3);
        }
    });

    std::cout << f(N) << std::endl;
}
