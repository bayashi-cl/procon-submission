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
    n, k = map(int, sinput().split())
    h = [int(sinput()) for _ in range(n)]
    h.sort()
    ans = INF
    for i in range(n):
        try:
            ans = min(ans, h[i + k - 1] - h[i])
        except IndexError:
            break
    print(ans)


if __name__ == "__main__":
    main()
