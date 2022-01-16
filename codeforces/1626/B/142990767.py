import functools
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple


sys.setrecursionlimit(10 ** 6)
sinput: Callable[..., str] = sys.stdin.readline
debug = functools.partial(print, file=sys.stderr)
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2


def main() -> None:
    s = sinput().strip()
    l = len(s)
    same_pos = -1
    for i in range(l - 1):
        af = int(s[i]) + int(s[i + 1])
        if af >= 10:
            same_pos = i
    if same_pos != -1:
        change_pos = same_pos
    else:
        change_pos = 0

    print(
        s[:change_pos],
        int(s[change_pos]) + int(s[change_pos + 1]),
        s[change_pos + 2 :],
        sep="",
    )


if __name__ == "__main__":
    t = int(sinput())
    for _ in range(t):
        main()
