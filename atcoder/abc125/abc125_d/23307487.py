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
    s = np.sum(np.abs(a))
    if np.any(a == 0):
        print(s)
        return

    neg_cnt = np.count_nonzero(a < 0)
    if neg_cnt % 2 == 0:
        print(s)
        return

    min_abs = np.min(np.abs(a))
    print(s - 2 * min_abs)


if __name__ == "__main__":
    main()
