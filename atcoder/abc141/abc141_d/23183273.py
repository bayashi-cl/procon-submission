# region template
import sys
import typing
import heapq

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
    a = list(map(lambda x: -int(x), sinput().split()))
    heapq.heapify(a)

    for i in range(m):
        s = heapq.heappop(a)
        s = -(-s // 2)
        heapq.heappush(a, s)

    print(-sum(a))


if __name__ == "__main__":
    main()
