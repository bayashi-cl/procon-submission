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
    n = int(sinput())
    V = list(map(int, sinput().split()))
    C = list(map(int, sinput().split()))
    ans = 0
    for v, c in zip(V, C):
        ans += max(v - c, 0)
    print(ans)


if __name__ == "__main__":
    main()
