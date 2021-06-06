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
    b = list(map(int, sinput().split()))
    ans = 0
    for i in range(n):
        ans += min(a[i], b[i])
        r = max(b[i] - a[i], 0)
        if r > 0:
            ans += min(a[i + 1], r)
            a[i + 1] = max(a[i + 1] - r, 0)

    print(ans)


if __name__ == "__main__":
    main()
