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
    k, n = map(int, sinput().split())
    a = np.array(list(map(int, sinput().split())), dtype=np.int64)

    max_diff = np.max(np.diff(a))
    top_diff = k - a[-1] + a[0]
    max_diff = max(max_diff, top_diff)
    print(k - max_diff)


if __name__ == "__main__":
    main()
