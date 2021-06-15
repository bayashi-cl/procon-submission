# region template
import sys
import typing
from operator import itemgetter

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
    order = [tuple(map(int, sinput().split())) for _ in range(m)]
    order.sort(key=itemgetter(1))
    fall = -1
    ans = 0
    for a, b in order:
        if fall < a:
            ans += 1
            fall = b - 1
    print(ans)


if __name__ == "__main__":
    main()
