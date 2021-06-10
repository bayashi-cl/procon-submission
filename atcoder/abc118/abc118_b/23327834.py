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
    food = [0] * (m + 1)

    for _ in range(n):
        k, *a = map(int, sinput().split())
        for ai in a:
            food[ai] += 1

    print(food.count(n))


if __name__ == "__main__":
    main()
