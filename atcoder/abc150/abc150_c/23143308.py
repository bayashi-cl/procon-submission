# region template
import sys
import typing
from itertools import permutations

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
    p = tuple(map(int, sinput().split()))
    q = tuple(map(int, sinput().split()))

    perm = list(permutations(range(1, n + 1)))
    ans = abs(perm.index(p) - perm.index(q))
    print(ans)


if __name__ == "__main__":
    main()
