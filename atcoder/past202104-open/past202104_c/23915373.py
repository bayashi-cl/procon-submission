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
    n, m = map(int, sinput().split())
    phone = []
    for _ in range(n):
        k, *a = map(int, sinput().split())
        phone.append(set(a))

    p, q = map(int, sinput().split())
    req = set(map(int, sinput().split()))
    ans = 0
    for cell in phone:
        if len(cell & req) >= q:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
