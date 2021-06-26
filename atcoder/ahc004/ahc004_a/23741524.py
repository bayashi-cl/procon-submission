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
    n, m = map(int, sinput().split())
    s = [sinput().strip() for _ in range(m)]
    s.sort(key=lambda x: len(x), reverse=True)
    ans_ = s[:n]
    ans = []
    for a in ans_:
        ans.append(a + "." * (n - len(a)))
    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
