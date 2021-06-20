# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    s = [sinput().strip() for _ in range(n)]
    s_cnt = Counter(s)
    m = int(sinput())
    t = [sinput().strip() for _ in range(m)]
    t_cnt = Counter(t)

    ans = 0
    for k, v in s_cnt.items():
        ans = max(ans, v - t_cnt[k])

    print(ans)


if __name__ == "__main__":
    main()
