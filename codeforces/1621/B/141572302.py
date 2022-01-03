# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    n = int(sinput())
    lrc = [tuple(map(int, sinput().split())) for _ in range(n)]
    ans1 = [[0, 0] for _ in range(n)]  # w, c
    max_w = 0
    min_c = IINF
    for i, (l, r, c) in enumerate(lrc):
        if r - l + 1 > max_w:
            max_w = r - l + 1
            min_c = c
        elif r - l + 1 == max_w:
            min_c = min(min_c, c)
        ans1[i] = [max_w, min_c]
        # if r - l + 1 > max_w:
        #     max_w = r - l + 1
        #     ans1[i] = [r - l + 1, c]
        # elif r - l + 1 == max_w:
        #     ans1[i] = ans1[i - 1]
        #     ans1[i][1] = min(ans1[i - 1][1], c)
        # else:
        #     ans1[i] = ans1[i - 1]

    ans2 = [[0, 0] for _ in range(n)]

    left = IINF
    right = -IINF
    left_cost = -1
    right_cost = -1
    for i, (l, r, c) in enumerate(lrc):
        if l < left:
            left = l
            left_cost = c
        elif l == left:
            left_cost = min(left_cost, c)

        if r > right:
            right = r
            right_cost = c
        elif r == right:
            right_cost = min(right_cost, c)

        ans2[i] = [right - left + 1, left_cost + right_cost]

    for i in range(n):
        if ans1[i][0] == ans2[i][0]:
            print(min(ans1[i][1], ans2[i][1]))
        elif ans1[i][0] > ans2[i][0]:
            print(ans1[i][1])
        else:
            print(ans2[i][1])


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
