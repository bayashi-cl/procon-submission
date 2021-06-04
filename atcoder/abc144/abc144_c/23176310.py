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
    dist = INF
    n = int(sinput())
    i = 1
    while i * i <= n:
        if n % i == 0:
            dist = min(dist, i + n // i - 2)
        i += 1
    print(dist)


if __name__ == "__main__":
    main()
