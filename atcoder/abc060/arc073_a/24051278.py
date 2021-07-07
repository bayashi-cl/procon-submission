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
    n, t = map(int, sinput().split())
    push = list(map(int, sinput().split()))
    ans = t
    for i in range(n - 1):
        ans += min(t, push[i + 1] - push[i])

    print(ans)


if __name__ == "__main__":
    main()
