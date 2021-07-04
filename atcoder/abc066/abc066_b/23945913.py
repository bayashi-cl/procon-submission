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
    s = list(sinput().strip())
    while True:
        s.pop()
        if len(s) % 2 == 1:
            continue
        if s[: len(s) // 2] == s[len(s) // 2 :]:
            print(len(s))
            break


if __name__ == "__main__":
    main()
