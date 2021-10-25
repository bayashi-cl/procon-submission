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
    x = 1000 - int(sinput())
    ans = 0
    d, x = divmod(x, 500)
    ans += d
    d, x = divmod(x, 100)
    ans += d
    d, x = divmod(x, 50)
    ans += d
    d, x = divmod(x, 10)
    ans += d
    d, x = divmod(x, 5)
    ans += d
    ans += x

    print(ans)


if __name__ == "__main__":
    main()
