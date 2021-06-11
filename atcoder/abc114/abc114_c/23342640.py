# region template
import sys
import typing
from itertools import product

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def make_int(perm: tuple) -> int:
    res = 0
    for p in perm:
        res = res * 10 + p
    return res


def main() -> None:
    num = (3, 5, 7)

    n = int(sinput())
    d = len(str(n))
    ans = 0
    for i in range(3, d + 1):
        for perm in product(num, repeat=i):
            if len(set(perm)) <= 2:
                continue
            if make_int(perm) > n:
                continue
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
