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

    s = sum(a)
    other = sum(a[i] for i in range(1, n, 2))
    r0 = s - 2 * other
    ans = [r0]

    for i in range(n - 1):
        r1 = 2 * a[i] - r0
        ans.append(r1)
        r0 = r1

    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    main()
