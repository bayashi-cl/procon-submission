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
    s = list(sinput().strip())
    k = int(sinput())
    k -= 1
    c = s[k]
    for i in range(n):
        if s[i] != c:
            s[i] = "*"

    print("".join(s))


if __name__ == "__main__":
    main()
