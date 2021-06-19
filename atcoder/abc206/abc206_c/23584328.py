# region template
import sys
import typing
from collections import Counter

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

    ans = n * (n - 1) // 2
    cnt = Counter(a)
    for v in cnt.values():
        ans -= v * (v - 1) // 2
    print(ans)


if __name__ == "__main__":
    main()
