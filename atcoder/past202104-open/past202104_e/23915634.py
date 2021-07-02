# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import deque

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a = deque()

    _ = int(sinput())
    s = sinput().strip()
    for i, si in enumerate(s):
        if si == "L":
            a.appendleft(i + 1)
        if si == "R":
            a.append(i + 1)
        if si == "A":
            if len(a) <= 0:
                print("ERROR")
            else:
                print(a.popleft())
        if si == "B":
            if len(a) <= 1:
                print("ERROR")
            else:
                print(a[1])
                del a[1]
        if si == "C":
            if len(a) <= 2:
                print("ERROR")
            else:
                print(a[2])
                del a[2]
        if si == "D":
            if len(a) <= 0:
                print("ERROR")
            else:
                print(a.pop())
        if si == "E":
            if len(a) <= 1:
                print("ERROR")
            else:
                print(a[-2])
                del a[-2]
        if si == "F":
            if len(a) <= 2:
                print("ERROR")
            else:
                print(a[-3])
                del a[-3]


if __name__ == "__main__":
    main()
