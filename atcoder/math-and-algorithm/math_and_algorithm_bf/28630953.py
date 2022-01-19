import functools
import sys
import typing
import math
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    n = int(sinput())
    abc = [tuple(map(int, sinput().split())) for _ in range(n)]

    ans = 0.0
    for i in range(n):
        for j in range(i + 1, n):
            a, b, c = abc[i]
            p, q, r = abc[j]
            if math.isclose(a * q, p * b):
                continue
            y = (p * c - r * a) / (p * b - q * a)
            x = (c - b * y) / a

            for s, t, u in abc:
                if not math.isclose(s * x + t * y, u) and s * x + t * y > u:
                    break
            else:
                ans = max(ans, x + y)

    print(ans)


if __name__ == "__main__":
    main()
