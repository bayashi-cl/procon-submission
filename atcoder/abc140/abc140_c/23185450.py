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
    b = list(map(int, sinput().split()))

    ans = [INF] * n
    for i in range(1, n):
        ans[i - 1] = min(ans[i - 1], b[i - 1])
        ans[i] = b[i - 1]
    print(sum(ans))


if __name__ == "__main__":
    main()
