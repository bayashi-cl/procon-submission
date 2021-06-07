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


def main() -> None:
    n, d = map(int, sinput().split())
    sq = {i ** 2 for i in range(401)}
    pos = [tuple(map(int, sinput().split())) for _ in range(n)]
    ans = 0
    for i in range(n - 1):
        for j in range(i + 1, n):
            dist2 = 0
            for x, y in zip(pos[i], pos[j]):
                dist2 += (x - y) ** 2
            if dist2 in sq:
                ans += 1
    print(ans)


if __name__ == "__main__":
    main()
