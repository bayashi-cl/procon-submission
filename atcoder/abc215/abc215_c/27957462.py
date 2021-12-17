# region template
import sys
import typing
from itertools import permutations
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
    s_, k_ = sinput().split()
    s = list(s_)
    k = int(k_)
    ans = list(set(permutations(s)))
    ans.sort()
    print("".join(ans[k - 1]))


if __name__ == "__main__":
    main()
