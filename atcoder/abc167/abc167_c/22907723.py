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


def bit2set(n: int) -> typing.Set[int]:
    res = set()
    for i in range(n.bit_length()):
        if not (1 << i & n) == 0:
            res.add(i)
    return res


def main() -> None:
    n, m, x = map(int, sinput().split())
    cost = [0] * n
    book = []
    for i in range(n):
        c, *a = map(int, sinput().split())
        cost[i] = c
        book.append(a)

    min_plice = INF
    for i in range(1 << n):
        skill = [0] * m
        idx = bit2set(i)
        plice = 0
        for bi in idx:
            b = book[bi]
            plice += cost[bi]
            for j in range(m):
                skill[j] += b[j]
        if min(skill) >= x:
            min_plice = min(min_plice, plice)

    if min_plice == INF:
        print(-1)
    else:
        print(min_plice)


if __name__ == "__main__":
    main()
