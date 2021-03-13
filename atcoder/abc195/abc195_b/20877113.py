# region template
from __future__ import annotations

import math
import sys
from typing import Any, Callable, Final


def plog(*obj: Any) -> None:
    print(*obj, file=sys.stderr)


sys.setrecursionlimit(10 ** 9)
sinput: Callable[[], str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    a, b, w = map(int, sinput().split())
    w *= 1000
    ma = int(w / a)
    mi = math.ceil(w / b)
    if ma < mi:
        print("UNSATISFIABLE")
    else:
        print(mi, ma)


if __name__ == "__main__":
    main()
