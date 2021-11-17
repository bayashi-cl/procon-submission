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
    s = sinput().strip()
    t = sinput().strip()
    ans = INF
    for i in range(len(s) - len(t) + 1):
        cnt = 0
        for si, ti in zip(s[i : i + len(t)], t):
            if si != ti:
                cnt += 1
        ans = min(ans, cnt)
    print(ans)


if __name__ == "__main__":
    main()
