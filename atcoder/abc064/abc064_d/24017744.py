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
    cnt = 0
    lack = 0
    for si in s:
        if si == "(":
            cnt += 1
        else:
            cnt -= 1

        lack = min(lack, cnt)

    lack *= -1
    ans = "(" * lack + s + ")" * (cnt + lack)

    print(ans)


if __name__ == "__main__":
    main()
