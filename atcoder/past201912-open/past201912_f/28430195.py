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
    s = sinput().strip()
    d = []
    l = 0
    for r in range(len(s)):
        if l == r:
            continue
        if s[r].isupper():
            d.append(s[l : r + 1])
            l = r + 1
    d.sort(key=str.lower)
    print("".join(d))


if __name__ == "__main__":
    main()
