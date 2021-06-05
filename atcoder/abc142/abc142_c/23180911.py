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
    idx = np.argsort(a)
    print(" ".join(map(lambda x: str(x + 1), idx.tolist())))


if __name__ == "__main__":
    main()
