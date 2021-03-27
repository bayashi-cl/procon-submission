# region template
import sys
from typing import Any, Callable
from itertools import combinations


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


def calc_or(li: list) -> int:
    res = 0
    for l in li:
        res = res | l
    return res


def calc_xor(li: list) -> int:
    res = 0
    for l in li:
        res = res ^ l
    return res


def main() -> None:
    N = int(sinput())
    A = list(map(int, sinput().split()))
    ans = INF

    for i in range(1, N + 1):
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
