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
    h = int(sinput())
    ans = 0
    mons = 1
    while h > 1:
        ans += mons
        mons <<= 1
        h >>= 1
    print(ans + mons)


if __name__ == "__main__":
    main()
