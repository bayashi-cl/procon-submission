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
    n, m = map(int, sinput().split())
    cnt = [0] * n
    for _ in range(m):
        a, b = map(int, sinput().split())
        a -= 1
        b -= 1
        if a > b:
            cnt[a] += 1
        elif a < b:
            cnt[b] += 1

    print(cnt.count(1))


if __name__ == "__main__":
    main()
