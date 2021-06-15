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
    a = list(map(int, sinput().split()))
    a.sort()
    ans = 0
    for i in range(2):
        ans += abs(a[i] - a[i + 1])
    print(ans)


if __name__ == "__main__":
    main()
