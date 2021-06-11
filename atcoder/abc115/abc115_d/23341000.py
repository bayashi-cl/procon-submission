# region template
import sys
import typing
from functools import lru_cache

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, X = map(int, sinput().split())

    @lru_cache
    def burger(l: int) -> int:
        if l == 0:
            return 1
        else:
            return 2 * burger(l - 1) + 3

    @lru_cache
    def patty(l: int) -> int:
        if l == 0:
            return 1
        else:
            return 2 * patty(l - 1) + 1

    @lru_cache
    def solve(level: int, x: int) -> int:  # 下からx枚にパティが何枚あるか
        if level == 0:
            return 1

        if x <= 1:
            return 0
        elif 1 < x and x <= burger(level - 1) + 1:
            return solve(level - 1, x - 1)
        elif x == burger(level - 1) + 2:
            return patty(level - 1) + 1
        elif burger(level - 1) + 2 < x and x < burger(level):
            return patty(level - 1) + 1 + solve(level - 1, x - (burger(level - 1) + 2))
        elif x >= burger(level):
            return patty(level)
        else:
            raise ValueError

    print(solve(n, X))


if __name__ == "__main__":
    main()
