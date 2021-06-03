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
    n, m = map(int, sinput().split())
    ac = [False] * (n + 1)
    pen = [0] * (n + 1)
    for _ in [None] * m:
        p_, s = sinput().split()
        p = int(p_)
        if s == "AC":
            ac[p] = True
        else:
            if not ac[p]:
                pen[p] += 1

    n_pen = 0
    n_ac = 0

    for a, pe in zip(ac, pen):
        if a:
            n_ac += 1
            n_pen += pe

    print(n_ac, n_pen)


if __name__ == "__main__":
    main()
