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
    n, m = map(int, sinput().split())
    a = np.array([0] + list(map(int, sinput().split())) + [n + 1], dtype=np.int64)
    a.sort()
    diff_ = np.diff(a) - 1
    diff = diff_[diff_ != 0]
    if len(diff) == 0:
        print(0)
        return
    k = np.min(diff)
    ans = np.sum(np.ceil(diff / k))
    print(int(ans))


if __name__ == "__main__":
    main()
