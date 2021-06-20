# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion

"""
n人がx分間隔で順次コンテストに参加
コンテストにかかる時間はt
各参加者が終了した時点でまだコンテストに参加している人の合計
"""


def solve(n: int, x: int, t: int) -> int:
    one = t // x

    if one >= n:
        ans = n * (n - 1) // 2
    else:
        ans = one * (one - 1) // 2 + one * (n - one)
    return ans


def main() -> None:
    k = int(sinput())
    for _ in range(k):
        n, x, t = map(int, sinput().split())
        print(solve(n, x, t))


if __name__ == "__main__":
    main()
