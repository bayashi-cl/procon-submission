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
    s = sinput().strip()
    n = len(s)
    if n % 2 == 1:
        print("NO")
        return

    if s[: n // 2] == s[n // 2 :]:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
