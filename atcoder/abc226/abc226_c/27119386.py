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
    t = [0] * n
    a = []
    for i in range(n):
        ti, _, *ai = map(lambda x: int(x) - 1, sinput().split())
        t[i] = ti + 1
        a.append(ai)
    s = set()
    s.add(n - 1)

    for i in reversed(range(n)):
        if i in s:
            for aij in a[i]:
                s.add(aij)
    ans = 0
    for si in s:
        ans += t[si]
    print(ans)


if __name__ == "__main__":
    main()
