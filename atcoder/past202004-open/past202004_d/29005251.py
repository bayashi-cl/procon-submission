import functools
import sys
import typing
import re
import string
import itertools
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    s = sinput().strip()
    c = list(string.ascii_lowercase)
    c.append(".")
    ans = 0
    for r in [1, 2, 3]:
        for p in itertools.product(c, repeat=r):
            if re.search("".join(p), s) is not None:
                ans += 1
    print(ans)


if __name__ == "__main__":
    main()
