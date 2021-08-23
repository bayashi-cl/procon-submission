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
    n = int(sinput())
    ans = [0] * (n + 1)
    x = 1
    while x ** 2 <= n:
        y = 1
        while y ** 2 <= n:
            z = 1
            while z ** 2 <= n:
                fx = x ** 2 + y ** 2 + z ** 2 + x * y + y * z + z * x
                if fx > n:
                    break
                ans[fx] += 1
                z += 1
            y += 1
        x += 1

    print(*ans[1::], sep="\n")


if __name__ == "__main__":
    main()
