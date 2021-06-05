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
    n, k = map(int, sinput().split())
    s = sinput().strip()
    cp = [s[0]]

    for si in s:
        if si != cp[-1]:
            cp.append(si)

    cp_l = "".join(cp)
    cp_r = "".join(cp)
    cp_l = cp_l.replace("L", "R", k)
    cp_r = cp_r.replace("R", "L", k)

    prev = cp_l[0]
    uf1 = 0
    for c in cp_l:
        if c != prev:
            uf1 += 1
            prev = c

    prev = cp_r[0]
    uf2 = 0
    for c in cp_r:
        if c != prev:
            uf2 += 1
            prev = c

    print(max(n - uf1 - 1, n - uf2 - 1))


if __name__ == "__main__":
    main()
