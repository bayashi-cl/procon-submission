# region template
import sys
import typing
from itertools import combinations

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, a, b, c = map(int, sinput().split())
    bamboo = list(map(int, sys.stdin.read().split()))
    ans = INF

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i + j > n:
                break
            for k in range(1, n + 1):
                if i + j + k > n:
                    break
                mp_synth = (i + j + k - 3) * 10
                s = set(range(n))

                for p in combinations(s, i):
                    sp = s - set(p)
                    x = sum(bamboo[idx] for idx in p)
                    for q in combinations(sp, j):
                        spq = sp - set(q)
                        y = sum(bamboo[idx] for idx in q)
                        for r in combinations(spq, k):
                            z = sum(bamboo[idx] for idx in r)

                            bamboo_u = [x, y, z]
                            bamboo_u.sort()
                            mp = mp_synth
                            mp += abs(a - bamboo_u[2])
                            mp += abs(b - bamboo_u[1])
                            mp += abs(c - bamboo_u[0])
                            ans = min(ans, mp)

    print(ans)


if __name__ == "__main__":
    main()
