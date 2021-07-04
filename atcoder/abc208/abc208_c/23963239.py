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
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    p = dict()
    d, m = divmod(k, n)
    for ai in a:
        p[ai] = d
    a_s = sorted(a)
    for asi in a_s[:m]:
        p[asi] += 1

    for ai in a:
        print(p[ai])


if __name__ == "__main__":
    main()
