import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def s(x: int) -> int:
    return x * (x + 1) // 2 % MOD


def main() -> None:
    n = int(sinput())
    d = 1
    ans = 0
    while True:
        if d * 10 <= n:
            ans += s(d * 10 - d)
            ans %= MOD
        else:
            ans += s(n - d + 1)
            ans %= MOD
            break

        d *= 10

    print(ans)


if __name__ == "__main__":
    main()
