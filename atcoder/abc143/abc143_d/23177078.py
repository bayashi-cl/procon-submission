# region template
import sys
import typing
from bisect import bisect_left


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
    l = list(map(int, sinput().split()))
    l.sort()
    ans = 0
    for i in range(n - 2):
        for j in range(i + 1, n - 1):
            th = l[i] + l[j]
            if l[j + 1] >= th:
                continue
            ans += bisect_left(l, th) - j - 1

    print(ans)


if __name__ == "__main__":
    main()
