# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
from collections import deque

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    S = sinput().strip()
    T = deque()
    rev = False
    for s in S:
        if s == "R":
            rev = not rev
        elif not T:
            T.append(s)
        elif rev:
            if T[0] == s:
                T.popleft()
            else:
                T.appendleft(s)
        else:
            if T[-1] == s:
                T.pop()
            else:
                T.append(s)
    if rev:
        T.reverse()
    print("".join(T))


if __name__ == "__main__":
    main()
