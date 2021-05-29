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
    x = np.zeros(n, dtype=np.int64)
    y = np.zeros(n, dtype=np.int64)

    for i in range(n):
        xi, yi = map(int, sinput().split())
        x[i] = xi
        y[i] = yi

    arg_x = np.argsort(x)
    x = x[arg_x]
    arg_y = np.argsort(y)
    y = y[arg_y]

    if x[-1] - x[0] >= y[-1] - y[0]:
        # first = x[-1] - x[0]
        if set(arg_y[[0, -1]]) == set(arg_x[[0, -1]]):
            ans = max(x[-1] - x[1], x[-2] - x[0], y[-1] - y[1], y[-2] - y[0])
        else:
            ans = max(x[-1] - x[1], x[-2] - x[0], y[-1] - y[0])

    else:
        # first = y[-1] - y[0]
        if set(arg_x[[0, -1]]) == set(arg_y[[0, -1]]):
            ans = max(y[-1] - y[1], y[-2] - y[0], x[-1] - x[1], x[-2] - x[0])
        else:
            ans = max(y[-1] - y[1], y[-2] - y[0], x[-1] - x[0])

    print(ans)


if __name__ == "__main__":
    main()
