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
    ans = int(s) + int(s[1:] + s[0]) + int(s[2] + s[:2])
    print(ans)


if __name__ == "__main__":
    main()
