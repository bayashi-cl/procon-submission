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
    h, w = map(int, sinput().split())
    if h % 3 == 0 or w % 3 == 0:
        print(0)
        return

    ans = min(h, w)

    for i in range(1, h):
        p1 = w * i
        p2 = (w // 2) * (h - i)
        p3 = (w - w // 2) * (h - i)

        diff = max(p1, p2, p3) - min(p1, p2, p3)
        ans = min(ans, diff)

    for j in range(w):
        p1 = h * j
        p2 = (h // 2) * (w - j)
        p3 = (h - h // 2) * (w - j)

        diff = max(p1, p2, p3) - min(p1, p2, p3)
        ans = min(ans, diff)

    print(ans)


if __name__ == "__main__":
    main()
