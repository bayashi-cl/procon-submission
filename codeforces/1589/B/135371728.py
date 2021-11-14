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


def solve(m: int, n: int) -> int:
    div, mod = divmod(m, 3)
    res = div * n

    res += (n + 2) // 3 * mod
    return res


def main() -> None:
    t = int(sinput())
    for _ in range(t):
        n, m = map(int, sinput().split())
        ans = min(solve(n, m), solve(m, n))
        print(ans)


if __name__ == "__main__":
    main()
