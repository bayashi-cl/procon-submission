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
    h, w = map(int, sinput().split())
    a = [list(map(int, sinput().split())) for _ in range(h)]

    for i1 in range(h):
        for i2 in range(i1 + 1, h):
            for j1 in range(w):
                for j2 in range(j1 + 1, w):
                    if a[i1][j1] + a[i2][j2] > a[i2][j1] + a[i1][j2]:
                        print("No")
                        return
    print("Yes")


if __name__ == "__main__":
    main()
