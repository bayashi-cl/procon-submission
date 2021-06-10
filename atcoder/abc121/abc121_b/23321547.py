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
    n, m, c = map(int, sinput().split())
    b = np.array(list(map(int, sinput().split())))
    a = np.array([list(map(int, sinput().split())) for _ in range(n)])
    ans = np.count_nonzero((a @ b) > -c)
    print(ans)


if __name__ == "__main__":
    main()
