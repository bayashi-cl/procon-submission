# region template
import sys
import typing

import numpy as np

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    a = np.array(list(map(int, sinput().split())))

    cscs = np.cumsum(np.cumsum(a))
    mx = np.maximum.accumulate(a)

    for k in range(n):
        print((k + 1) * mx[k] + cscs[k])


if __name__ == "__main__":
    main()
