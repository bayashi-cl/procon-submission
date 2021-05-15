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
    n, k = map(int, sinput().split())
    c = [0] * (n + 1)
    for i in range(2, n + 1):
        if c[i] == 0:
            for j in range(i, n + 1, i):
                c[j] += 1
    ans = 0
    for i in range(1, n + 1):
        if c[i] >= k:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
