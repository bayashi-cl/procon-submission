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
    a, b, c = map(int, sinput().split())

    ea = b - (c - b)
    if ea % a == 0 and ea // a > 0:
        print("YES")
        return

    eb = (a + c) // 2
    if (a + c) % 2 == 0 and eb % b == 0 and eb // b > 0:
        print("YES")
        return

    ec = b + (b - a)
    if ec % c == 0 and ec // c > 0:
        print("YES")
        return
    print("NO")


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
