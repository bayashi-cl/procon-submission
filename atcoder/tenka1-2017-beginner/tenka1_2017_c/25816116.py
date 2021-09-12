# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from math import isclose

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def judge(N, h, w, n):
    left = 4 / N
    right = 1 / h + 1 / w + 1 / n
    return isclose(left, right)


# -Nhn = (Nn + Nh - 4hn)w
def main() -> None:
    N = int(sinput())

    for h in range(1, 3501):
        for n in range(1, 3501):
            left = -N * h * n
            right = N * n + N * h - 4 * h * n
            if right == 0:
                continue
            if left % right == 0:
                w = left // right
                if w <= 0:
                    continue
                # print(judge(N, h, n, w), file=sys.stderr)
                print(h, n, w)
                return


if __name__ == "__main__":
    main()
