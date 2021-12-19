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
    a = ord("a")
    s = list(map(lambda x: ord(x) - a, sinput().strip()))
    t = list(map(lambda x: ord(x) - a, sinput().strip()))

    d = (t[0] - s[0]) % 26
    for si, ti in zip(s, t):
        if (ti - si) % 26 != d:
            print("No")
            return

    print("Yes")


if __name__ == "__main__":
    main()
