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
    have = [False] * n
    for _ in range(k):
        _ = int(sinput())
        a = list(map(int, sinput().split()))
        for ai in a:
            have[ai - 1] = True

    print(n - sum(have))


if __name__ == "__main__":
    main()
