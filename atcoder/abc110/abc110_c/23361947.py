# region template
import sys
import typing
from collections import Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    s = list(sinput().strip())
    t = list(sinput().strip())

    d_s = dict()
    cnt = 0
    kind_s = []
    for si in s:
        if si in d_s:
            kind_s.append(d_s[si])
        else:
            d_s[si] = cnt
            kind_s.append(cnt)
            cnt += 1

    d_t = dict()
    cnt = 0
    kind_t = []
    for ti in t:
        if ti in d_t:
            kind_t.append(d_t[ti])
        else:
            d_t[ti] = cnt
            kind_t.append(cnt)
            cnt += 1

    if kind_s == kind_t:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
