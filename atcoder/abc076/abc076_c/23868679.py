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
    s = list(sinput().strip())
    t = list(sinput().strip())

    pos = -1
    for i in range(len(s) - len(t) + 1):
        for j in range(i, i + len(t)):
            if s[j] == "?":
                continue
            if s[j] == t[j - i]:
                continue

            break
        else:
            pos = i

    if pos == -1:
        print("UNRESTORABLE")
        return

    s[pos : pos + len(t)] = t
    for i in range(len(s)):
        if s[i] == "?":
            s[i] = "a"
    print("".join(s))


if __name__ == "__main__":
    main()
