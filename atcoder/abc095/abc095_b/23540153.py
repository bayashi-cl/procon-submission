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
    n, x = map(int, sinput().split())
    m = [int(sinput()) for _ in range(n)]
    re = x - sum(m)
    ans = n + re // min(m)
    print(ans)


if __name__ == "__main__":
    main()
