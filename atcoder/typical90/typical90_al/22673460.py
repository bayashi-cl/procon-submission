# region template
import sys
import typing

import numpy as np

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b = map(int, sinput().split())
    lcm = np.lcm(a, b, dtype=object)
    if lcm > 10 ** 18:
        print("Large")
    else:
        print(int(lcm))


if __name__ == "__main__":
    main()
