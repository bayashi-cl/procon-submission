# region template
import sys
import typing
from bisect import bisect

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    r = []
    g = []
    b = []
    for _ in [None] * (n * 2):
        a, c = sinput().strip().split()
        if c == "R":
            r.append(int(a))
        elif c == "G":
            g.append(int(a))
        elif c == "B":
            b.append(int(a))
        else:
            raise ValueError

    r.sort()
    g.sort()
    b.sort()

    if len(r) % 2 == 0 and len(g) % 2 == 0 and len(b) % 2 == 0:
        print(0)
        return

    if len(r) % 2 == 0:
        x = g
        y = b
        z = r
    elif len(g) % 2 == 0:
        x = r
        y = b
        z = g
    elif len(b) % 2 == 0:
        x = g
        y = r
        z = b
    else:
        raise ValueError

    ans = INF

    # 奇数の色でペア
    for yi in y:
        if yi < x[0]:
            ans = min(ans, abs(yi - x[0]))
        elif yi >= x[-1]:
            ans = min(ans, abs(yi - x[-1]))
        else:
            idx = bisect(x, yi)
            ans = min(ans, abs(yi - x[idx]), abs(yi - x[idx - 1]))

    if len(z) == 0:
        print(ans)
        return

    # 偶数-奇数でペア*2
    cost1 = INF
    for xi in x:
        if xi < z[0]:
            cost1 = min(cost1, abs(xi - z[0]))
        elif xi >= z[-1]:
            cost1 = min(cost1, abs(xi - z[-1]))
        else:
            idx = bisect(z, xi)
            cost1 = min(cost1, abs(xi - z[idx]), abs(xi - z[idx - 1]))
    cost2 = INF
    for yi in y:
        if yi < z[0]:
            cost2 = min(cost2, abs(yi - z[0]))
        elif yi >= z[-1]:
            cost2 = min(cost2, abs(yi - z[-1]))
        else:
            idx = bisect(z, yi)
            cost2 = min(cost2, abs(yi - z[idx]), abs(yi - z[idx - 1]))
    ans = min(ans, cost1 + cost2)

    print(ans)


if __name__ == "__main__":
    main()
