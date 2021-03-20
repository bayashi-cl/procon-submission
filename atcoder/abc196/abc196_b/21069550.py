# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    x = sinput().strip()
    if "." in x:
        print(x.split(".")[0])
    else:
        print(x)


if __name__ == "__main__":
    main()
