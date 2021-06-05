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
    h = list(map(int, sinput().split()))
    ans = 0
    streak = 0
    for i in range(n - 1):
        if h[i] >= h[i + 1]:
            streak += 1
            ans = max(ans, streak)
        else:
            streak = 0
    print(ans)


if __name__ == "__main__":
    main()
