# region template
import sys
import typing
from bisect import bisect

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:

    n = int(sinput())
    vote = [0] * n
    ao = 0
    for i in range(n):
        a, b = map(int, sinput().split())
        ao += a
        vote[i] = 2 * a + b
    vote.sort(reverse=True)

    ta = 0
    for i in range(n):
        ta += vote[i]
        if ta > ao:
            print(i + 1)
            break


if __name__ == "__main__":
    main()
