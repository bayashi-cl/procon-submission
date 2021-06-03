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
    n, m = map(int, sinput().split())
    a = np.array(list(map(int, sinput().split())))
    a //= 2
    lcm = np.lcm.reduce(a)

    if np.any(lcm // a % 2 == 0):
        print(0)
        return

    ans = -(-(m // lcm) // 2)
    print(ans)


if __name__ == "__main__":
    main()
