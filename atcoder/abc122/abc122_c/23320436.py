# region template
import sys
import typing
from itertools import accumulate
from operator import add

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, q = map(int, sinput().split())
    s = sinput().strip()
    ac = [0] * n

    for i in range(n - 1):
        if s[i] == "A" and s[i + 1] == "C":
            ac[i] += 1

    ac = list(accumulate(ac, add, initial=0))
    for _ in range(q):
        l, r = map(int, sinput().split())
        ans = ac[r - 1] - ac[l - 1]
        print(ans)


if __name__ == "__main__":
    main()
