# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    _ = int(sinput())
    a, b = map(int, sinput().split())
    p = list(map(int, sinput().split()))

    q = 0
    r = 0
    s = 0
    for pi in p:
        if pi <= a:
            q += 1
        elif pi <= b:
            r += 1
        else:
            s += 1

    print(min(q, r, s))


if __name__ == "__main__":
    main()
