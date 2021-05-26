# region template
import sys
import typing
from math import gcd

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    k = int(sinput())
    ans = 0
    for a in range(1, k + 1):
        for b in range(1, k + 1):
            for c in range(1, k + 1):

                ans += gcd(a, gcd(b, c))

    print(ans)


if __name__ == "__main__":
    main()
