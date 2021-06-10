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
    n, m = map(int, sinput().split())
    shop = [tuple(map(int, sinput().split())) for _ in range(n)]
    shop.sort()

    bin = 0
    cash = 0
    for a, b in shop:
        num = min(b, m - bin)
        cash += a * num
        bin += num
        if bin == m:
            break
    print(cash)


if __name__ == "__main__":
    main()
