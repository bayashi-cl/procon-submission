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
    _ = int(sinput())
    s = sinput().strip()
    ans = 0
    for i in range(1000):
        i_str = str(i).zfill(3)
        p0 = s.find(i_str[0])
        if p0 == -1:
            continue
        p1 = s.find(i_str[1], p0 + 1)
        if p1 == -1:
            continue
        p2 = s.find(i_str[2], p1 + 1)
        if p2 == -1:
            continue

        ans += 1

    print(ans)


if __name__ == "__main__":
    main()
