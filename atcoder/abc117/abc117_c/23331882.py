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
    x = np.array(list(map(int, sinput().split())))
    x.sort()
    diff = np.diff(x)
    diff.sort()
    ans = np.sum(diff[: max(m - n, 0)])
    print(ans)


if __name__ == "__main__":
    main()
