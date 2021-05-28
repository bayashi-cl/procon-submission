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
    q = int(sinput())

    rev = False

    for _ in [None] * q:
        tfc = sinput().split()
        if tfc[0] == "1":
            rev = not rev
        else:
            if rev:
                if tfc[1] == "1":
                    s.append(tfc[2])
                if tfc[1] == "2":
                    s.appendleft(tfc[2])
            else:
                if tfc[1] == "1":
                    s.appendleft(tfc[2])
                if tfc[1] == "2":
                    s.append(tfc[2])

    if rev:
        ans = "".join(reversed(s))
    else:
        ans = "".join(s)
    print(ans)


if __name__ == "__main__":
    main()
