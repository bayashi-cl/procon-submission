# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n, a, b = map(int, sinput().split())
    p, q, r, s = map(int, sinput().split())
    ans = [["."] * (s - r + 1) for _ in range(q - p + 1)]
    for i in range(p, q + 1):
        for j in range(r, s + 1):
            if abs(i - a) == abs(j - b):
                ans[i - p][j - r] = "#"

    print(*map(lambda x: "".join(x), ans), sep="\n")


if __name__ == "__main__":
    main()
