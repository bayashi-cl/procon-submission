# region template
from __future__ import annotations

import sys
from typing import Callable, Final


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    menber = set()
    ident = []
    for i in range(1, n + 1):
        name = sinput().strip()
        if name in menber:
            continue
        else:
            menber.add(name)
            ident.append(i)

    print(" ".join(map(str, ident)))


if __name__ == "__main__":
    main()
