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
    x, y = map(int, sinput().split())
    ans = 1
    while True:
        if x * 2 ** ans > y:
            break
        ans += 1
    print(ans)


if __name__ == "__main__":
    main()
