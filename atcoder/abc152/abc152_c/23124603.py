# region template
import sys
import typing

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
    p = list(map(int, sinput().split()))
    mi = INF
    ans = 0
    for i in range(n):
        mi = min(mi, p[i])
        if mi >= p[i]:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
