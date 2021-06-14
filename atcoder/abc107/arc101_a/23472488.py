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
    x = list(map(int, sinput().split()))

    ans = INF
    for i in range(n):
        l = x[i]
        try:
            r = x[i + k - 1]
        except IndexError:
            break

        if r <= 0:
            ans = min(ans, -l)
        elif l >= 0:
            ans = min(ans, r)
        else:
            t = min(2 * r - l, 2 * (-l) + r)
            ans = min(ans, t)

    print(ans)


if __name__ == "__main__":
    main()
