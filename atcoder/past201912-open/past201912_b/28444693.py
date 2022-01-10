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
    ai = int(sinput())
    for _ in range(n - 1):
        nxt = int(sinput())
        if nxt == ai:
            print("stay")
        elif nxt < ai:
            print("down", ai - nxt)
        else:
            print("up", nxt - ai)
        ai = nxt


if __name__ == "__main__":
    main()
