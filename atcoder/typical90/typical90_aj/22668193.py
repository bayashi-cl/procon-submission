# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def m_dist(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def main() -> None:
    n, q = map(int, sinput().split())
    point = []
    minx, miny, maxx, maxy = IINF, IINF, -IINF, -IINF
    for _ in range(n):
        x, y = map(int, sinput().split())
        point.append((x - y, x + y))
        minx = min(minx, x - y)
        maxx = max(maxx, x - y)
        miny = min(miny, x + y)
        maxy = max(maxy, x + y)

    for _ in range(q):
        que = int(sinput())
        ret1 = abs(point[que - 1][0] - minx)
        ret2 = abs(point[que - 1][0] - maxx)
        ret3 = abs(point[que - 1][1] - miny)
        ret4 = abs(point[que - 1][1] - maxy)
        print(max(ret1, ret2, ret3, ret4))


if __name__ == "__main__":
    main()
