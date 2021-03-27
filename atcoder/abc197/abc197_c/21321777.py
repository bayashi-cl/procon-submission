# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
from itertools import combinations


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def calc_or(li: list) -> int:
    res = 0
    for l in li:
        res = res | l
    return res


def calc_xor(li: list) -> int:
    res = li[0]
    if len(li) == 1:
        return res

    for l in li[1:]:
        res = res ^ l
    return res


def main() -> None:
    N = int(sinput())
    A = list(map(int, sinput().split()))
    if N == 1:
        print(A[0])
        return
    ans = calc_xor(A)

    for i in range(2, N + 1):
        for sep in combinations(range(1, N), i - 1):
            before = 0
            or_list = list()
            for s in sep:
                or_list.append(calc_or(A[before:s]))
                before = s
            or_list.append(calc_or(A[before:]))
            ans = min(ans, calc_xor(or_list))

    print(ans)


if __name__ == "__main__":
    main()
