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
    adj: List[Set[int]] = [set() for _ in range(n)]
    for _ in range(m):
        a, b = map(lambda x: int(x) - 1, sinput().split())
        adj[a].add(b)
        adj[b].add(a)

    for relay in adj[0]:
        if n - 1 in adj[relay]:
            print("POSSIBLE")
            break
    else:
        print("IMPOSSIBLE")


if __name__ == "__main__":
    main()
