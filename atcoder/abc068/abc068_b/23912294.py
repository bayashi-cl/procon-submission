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
    br = 0
    ans = 1
    for i in range(1, n + 1):
        x = i
        cnt = 0
        while True:
            if x % 2 == 0:
                x //= 2
                cnt += 1
            else:
                break
        if cnt > br:
            br = cnt
            ans = i
    print(ans)


if __name__ == "__main__":
    main()
