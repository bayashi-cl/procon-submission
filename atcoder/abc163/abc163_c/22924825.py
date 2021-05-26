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
    a = list(map(int, sinput().split()))
    cnt = [0] * n

    for i in range(1, n):
        cnt[a[i - 1] - 1] += 1

    print(*cnt, sep="\n")


if __name__ == "__main__":
    main()
