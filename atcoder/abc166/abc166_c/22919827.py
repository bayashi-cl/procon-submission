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
    n, m = map(int, sinput().split())
    h = list(map(int, sinput().split()))
    adj = [[] for _ in range(n)]
    for _ in range(m):
        a, b = map(int, sinput().split())
        a -= 1
        b -= 1
        if h[a] >= h[b]:
            adj[b].append(a)
        if h[b] >= h[a]:
            adj[a].append(b)

    ans = 0
    for ad in adj:
        if len(ad) == 0:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
