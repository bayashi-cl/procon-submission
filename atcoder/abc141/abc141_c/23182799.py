# region template
import sys
import typing
from collections import Counter


sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, k, q = map(int, sinput().split())
    a = list(map(int, sys.stdin.read().split()))
    cnt = Counter(a)
    for i in range(1, n + 1):
        if k - q + cnt[i] > 0:
            print("Yes")
        else:
            print("No")


if __name__ == "__main__":
    main()
