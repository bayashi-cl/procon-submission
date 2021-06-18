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
    a, b, c, x, y = map(int, sinput().split())
    ans = INF
    for n_c in range(max(x * 2, y * 2) + 1):
        n_a = max(0, x - n_c // 2)
        n_b = max(0, y - n_c // 2)

        cost = a * n_a + b * n_b + c * n_c
        ans = min(ans, cost)

    print(ans)


if __name__ == "__main__":
    main()
