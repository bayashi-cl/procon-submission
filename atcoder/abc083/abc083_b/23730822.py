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
    n, a, b = map(int, sinput().split())
    ans = 0
    for i in range(1, n + 1):
        sm = 0
        for d in str(i):
            sm += int(d)
        if a <= sm and sm <= b:
            ans += i

    print(ans)


if __name__ == "__main__":
    main()
