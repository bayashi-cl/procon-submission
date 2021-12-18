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
    b = bin(n)[2:]
    ans = []
    for bi in b:
        if bi == "1":
            ans.append("A")
        ans.append("B")
    print("".join(ans[:-1]))


if __name__ == "__main__":
    main()
