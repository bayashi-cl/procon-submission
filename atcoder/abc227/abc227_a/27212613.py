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
    n, k, a = map(int, sinput().split())
    a -= 1
    for _ in range(k):
        a += 1
        a %= n
    if a == 0:
        a = n
    print(a)
    # print((a + k % n + 1) % n + 1)


if __name__ == "__main__":
    main()
