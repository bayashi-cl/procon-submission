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


def comb(n, r):
    shi = 1
    bo = 1
    for i in range(r):
        shi *= n - i
        bo *= r - i

        shi %= MOD
        bo %= MOD

    bo_mod = pow(bo, -1, MOD)
    return (shi * bo_mod) % MOD


def main() -> None:
    n, a, b = map(int, sinput().split())

    sncr = pow(2, n, MOD)
    nca = comb(n, a) % MOD
    ncb = comb(n, b) % MOD

    print((sncr - nca - ncb - 1) % MOD)


if __name__ == "__main__":
    main()
