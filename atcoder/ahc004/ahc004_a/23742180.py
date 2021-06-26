# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from itertools import combinations

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m = map(int, sinput().split())
    s = [sinput().strip() for _ in range(m)]
    s.sort(key=lambda x: len(x))
    pos = 0
    ans = []
    for i in range(n):
        l = 0
        line = ""
        while True:
            if l + len(s[pos]) <= n:
                line += s[pos]
                l += len(s[pos])
                pos += 1
            else:
                break
        ans.append(line + "." * (n - l))
    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
