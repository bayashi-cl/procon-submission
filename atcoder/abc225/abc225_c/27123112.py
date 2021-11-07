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
    n, m = map(int, sinput().split())
    b = [list(map(int, sinput().split())) for _ in range(n)]
    for i, bi in enumerate(b[0][:-1]):
        if b[0][i + 1] != bi + 1 or bi % 7 == 0:
            print("No")
            return

    for i in range(n - 1):
        for j in range(m):
            if b[i][j] + 7 != b[i + 1][j]:
                print("No")
                return

    print("Yes")


if __name__ == "__main__":
    main()
