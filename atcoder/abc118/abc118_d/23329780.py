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
    n, m = map(int, sinput().split())
    a = tuple(map(int, sinput().split()))
    match = {1: 2, 2: 5, 3: 5, 4: 4, 5: 5, 6: 6, 7: 3, 8: 7, 9: 6}

    @lru_cache
    def dp(i):
        if i == 0:
            return 0
        elif i < 0:
            return -INF
        res = []
        for ai in a:
            res.append(dp(i - match[ai]) * 10 + ai)
        return max(res)

    print(dp(n))


if __name__ == "__main__":
    main()
