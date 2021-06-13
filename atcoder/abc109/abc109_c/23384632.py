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
    n, x = map(int, sinput().split())
    p = np.array(list(map(int, sinput().split())), dtype=np.int64)

    d = np.gcd.reduce(p - x)

    print(d)


if __name__ == "__main__":
    main()
