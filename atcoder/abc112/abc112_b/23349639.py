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
    n, T = map(int, sinput().split())
    ans = INF
    for _ in range(n):
        c, t = map(int, sinput().split())
        if t <= T:
            ans = min(ans, c)

    if ans == INF:
        print("TLE")
    else:
        print(ans)


if __name__ == "__main__":
    main()
