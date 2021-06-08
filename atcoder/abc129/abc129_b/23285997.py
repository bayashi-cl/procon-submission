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
    t = list(map(int, sinput().split()))

    ans = INF
    for i in range(n - 1):
        ans = min(ans, abs(sum(t[: i + 1]) - sum(t[i + 1 :])))
    print(ans)


if __name__ == "__main__":
    main()
