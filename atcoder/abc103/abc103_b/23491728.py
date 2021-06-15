# region template
import sys
import typing
from collections import deque

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    s = deque(sinput().strip())
    t = deque(sinput().strip())
    for i in range(len(s)):
        s.rotate(1)
        if s == t:
            print("Yes")
            break
    else:
        print("No")


if __name__ == "__main__":
    main()
