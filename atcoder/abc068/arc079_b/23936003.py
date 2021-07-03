# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    k = int(sinput())
    n = 50
    d, m = divmod(k, n)
    ans = [n - 1 + d] * n
    for i in range(m):
        for j in range(n):
            if i == j:
                ans[j] += n
            else:
                ans[j] -= 1

    print(n)
    print(*ans)


if __name__ == "__main__":
    main()
