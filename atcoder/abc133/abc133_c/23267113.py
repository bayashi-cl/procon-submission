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
    l, r = map(int, sinput().split())
    if r - l + 1 >= 2019:
        print(0)
        return

    m = [i % 2019 for i in range(l, r + 1)]
    ans = INF
    for i in range(len(m) - 1):
        for j in range(i + 1, len(m)):
            ans = min(ans, m[i] * m[j] % 2019)

    print(ans)


if __name__ == "__main__":
    main()
