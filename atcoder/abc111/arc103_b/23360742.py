# region template
import sys
import typing

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
    pos = [tuple(map(int, sinput().split())) for _ in range(n)]
    pari = (abs(pos[0][0]) + abs(pos[0][1])) % 2
    for x, y in pos:
        if (abs(x) + abs(y)) % 2 != pari:
            print(-1)
            return

    m = 31
    arm = [2 ** i for i in reversed(range(m))]
    if not pari:
        m = 32
        arm.append(1)
    print(m)
    print(*arm)

    for x, y in pos:
        u, v = x - y, x + y
        ans = []
        now_u, now_v = 0, 0
        for a in arm:
            if u >= now_u:
                yoko = True
                now_u += a
            else:
                yoko = False
                now_u -= a

            if v >= now_v:
                tate = True
                now_v += a
            else:
                tate = False
                now_v -= a

            if yoko and tate:
                ans.append("R")
            elif (yoko is True) and (tate is False):
                ans.append("D")
            elif (yoko is False) and (tate is True):
                ans.append("U")
            elif (yoko is False) and (tate is False):
                ans.append("L")
            else:
                raise ValueError

        print("".join(ans))


if __name__ == "__main__":
    main()
