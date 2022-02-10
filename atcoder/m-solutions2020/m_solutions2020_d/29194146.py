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


def main() -> None:
    n = int(sinput())
    a = list(map(int, sinput().split()))
    a.append(0)
    money = 1000
    stock = 0

    up = False
    for i in range(n):
        if up:
            if a[i] > a[i + 1]:
                up = False
                money += a[i] * stock
                stock = 0
        else:
            if a[i] < a[i + 1]:
                up = True
                stock += money // a[i]
                money %= a[i]

    print(money)


if __name__ == "__main__":
    main()
