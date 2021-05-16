# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, m, t = map(int, sinput().split())
    r = n
    now = 0
    for _ in range(m):
        a, b = map(int, sinput().split())
        # arr
        r -= a - now
        if r <= 0:
            ans = "No"
            break
        now = a

        # dep
        r += b - now
        r = min(r, n)
        now = b
    else:
        r -= t - now
        if r <= 0:
            ans = "No"
        else:
            ans = "Yes"

    print(ans)


if __name__ == "__main__":
    main()
