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

    def f(x):
        lower = x * (x - 1) // 2
        upper = (n + (n - x + 1)) * x // 2
        return upper - lower + 1

    ans = 0
    for i in range(k, n + 2):
        ans += f(i)
        ans %= MOD

    print(ans)


if __name__ == "__main__":
    main()
