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
    n, k = map(int, sinput().split())
    ans = 0
    for i in range(1, n + 1):
        for j in range(1, k + 1):
            ans += 100 * i + j

    print(ans)


if __name__ == "__main__":
    main()
