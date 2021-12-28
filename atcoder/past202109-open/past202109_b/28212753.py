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
    sinput()
    a = set(map(int, sinput().split()))
    b = set(map(int, sinput().split()))
    ans = list(a & b)
    ans.sort()
    print(*ans)


if __name__ == "__main__":
    main()
