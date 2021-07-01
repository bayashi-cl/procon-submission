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
    n = int(sinput())
    p = list(map(int, sinput().split()))
    rle = []
    cnt = 0
    for i, pi in zip(range(1, n + 1), p):
        if pi == i:
            cnt += 1
        else:
            if cnt:
                rle.append(cnt)
                cnt = 0
    else:
        if cnt:
            rle.append(cnt)

    ans = 0
    for e in rle:
        ans += -(-e // 2)
    print(ans)


if __name__ == "__main__":
    main()
