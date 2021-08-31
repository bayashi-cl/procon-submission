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
    s = sinput().strip()
    white = [0] * n
    black = [0] * n
    for i, si in enumerate(s):
        if si == ".":
            white[i] = 1
        elif si == "#":
            black[i] = 1
        else:
            raise ValueError

    for i in range(n - 1):
        black[i + 1] += black[i]
    for i in reversed(range(1, n)):
        white[i - 1] += white[i]

    ans = min(white[0], black[-1])
    for i in range(1, n):
        ans = min(ans, black[i - 1] + white[i])

    print(ans)


if __name__ == "__main__":
    main()
