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
    n = sinput().strip()[::-1]
    ans = []
    for i, d in enumerate(n):
        if d == "0":
            continue
        ans.append(d + "0" * i)

    print(len(ans))
    print(*ans)


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
