# region template
import sys
import typing
from itertools import accumulate

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
    a = list(map(int, sinput().split()))
    ans = 0
    for i in range(max(a).bit_length()):
        zero = 0
        for ai in a:
            if (ai & (1 << i)) == 0:
                zero += 1
        ans += zero * (n - zero) * 2 ** i
    print(ans % MOD)


if __name__ == "__main__":
    main()
