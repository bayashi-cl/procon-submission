# region template
import sys
import typing

import numpy as np

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, C = map(int, sinput().split())
    event = []
    for _ in range(n):
        a, b, c = map(int, sinput().split())
        a -= 1
        event.append((a, c))
        event.append((b, -c))
    event.sort()
    ans = 0
    cost = 0
    day = 0
    for d, fee in event:
        if d != day:
            ans += min(C, cost) * (d - day)
            day = d
        cost += fee

    print(ans)


if __name__ == "__main__":
    main()
