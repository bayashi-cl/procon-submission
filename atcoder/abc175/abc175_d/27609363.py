# region template
import sys
import typing
from itertools import accumulate
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
    n, k = map(int, sinput().split())
    p = list(map(lambda x: int(x) - 1, sinput().split()))
    c = list(map(int, sinput().split()))
    ans = -IINF
    for i in range(n):
        now = i
        cycle_score = 0
        loop = 0

        while True:
            loop += 1
            cycle_score += c[now]
            now = p[now]
            if now == i:
                break

        path = 0
        cnt = 0

        while True:
            cnt += 1
            path += c[now]

            if cnt > k:
                break

            num = (k - cnt) // loop
            score = path + max(0, cycle_score) * num
            ans = max(ans, score)

            now = p[now]
            if now == i:
                break

    print(ans)


if __name__ == "__main__":
    main()
