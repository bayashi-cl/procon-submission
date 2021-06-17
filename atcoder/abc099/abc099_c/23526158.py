# region template
import sys
import typing
from functools import lru_cache

sys.setrecursionlimit(10 ** 8)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    one = set()
    one.add(1)
    k = 1
    while 6 ** k <= n:
        one.add(6 ** k)
        k += 1
    k = 1
    while 9 ** k <= n:
        one.add(9 ** k)
        k += 1

    @lru_cache(maxsize=None)
    def dp(x: int) -> int:
        if x < 0:
            return IINF

        if x in one:
            return 1

        res = IINF
        for o in one:
            res = min(res, dp(x - o))
        return res + 1

    print(dp(n))


if __name__ == "__main__":
    main()
