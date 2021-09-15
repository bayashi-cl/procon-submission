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
    s_ = list(sinput().strip())
    s = list(map(int, s_))
    d = sum(s[:-1:2]) * 3
    for i in s[1::2]:
        d += i
    if d % 10 == s[-1]:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
