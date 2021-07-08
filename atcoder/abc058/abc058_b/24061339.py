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
    o = sinput().strip()
    e = sinput().strip()
    ans = []
    if len(o) == len(e):
        for s, t in zip(o, e):
            ans.append(s)
            ans.append(t)
    else:
        for s, t in zip(o[:-1], e):
            ans.append(s)
            ans.append(t)
        ans.append(o[-1])

    print("".join(ans))


if __name__ == "__main__":
    main()
