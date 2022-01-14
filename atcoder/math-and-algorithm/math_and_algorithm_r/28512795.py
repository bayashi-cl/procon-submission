import functools
import sys
import typing
from collections import Counter
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    _ = int(sinput())
    a = list(map(int, sinput().split()))
    cnt = Counter(a)
    print(cnt[100] * cnt[400] + cnt[200] * cnt[300])


if __name__ == "__main__":
    main()
