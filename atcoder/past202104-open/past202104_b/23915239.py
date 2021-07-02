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
    s = sinput().strip()
    past = []
    i = 0
    while i + 4 <= len(s):
        past.append(s[i : i + 4])
        i += 4

    try:
        print(past.index("post") + 1)
    except ValueError:
        print("none")


if __name__ == "__main__":
    main()
