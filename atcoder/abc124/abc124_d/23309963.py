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
    n, k = map(int, sinput().split())
    s = sinput().strip()
    stand = []
    num = []
    cnt = 0
    st = s[0]
    for si in s:
        if si == st:
            cnt += 1
        else:
            num.append(cnt)
            stand.append(st)
            st = si
            cnt = 1
    else:
        num.append(cnt)
        stand.append(st)
    num_cs = list(accumulate(num, add, initial=0))
    l_cs = len(num_cs)

    ans = 0
    for i in range(int(stand[0]), l_cs, 2):
        r = min(l_cs - 1, i + 2 * k)
        l = max(i - 1, 0)
        ans = max(ans, num_cs[r] - num_cs[l])

    print(ans)


if __name__ == "__main__":
    main()
