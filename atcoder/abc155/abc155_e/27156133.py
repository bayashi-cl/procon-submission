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
    n = list(map(int, "0" + sinput().strip()))
    ans = 0
    for i in reversed(range(1, len(n))):
        if n[i] > 5 or (n[i] == 5 and n[i - 1] >= 5):
            ans += 10 - n[i]
            n[i - 1] += 1
        else:
            ans += n[i]
    ans += n[0]
    print(ans)


if __name__ == "__main__":
    main()
