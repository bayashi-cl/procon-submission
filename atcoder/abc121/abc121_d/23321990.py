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


def calc(n: int, i: int) -> int:
    d, m = divmod(n, 2 ** (i + 1))
    res = d * 2 ** i + max(m - 2 ** i, 0)
    return res


def main() -> None:
    a, b = map(int, sinput().split())
    w = b.bit_length()

    ans = []
    for i in range(w):
        one = calc(b + 1, i) - calc(a, i)
        ans.append(one % 2)

    ansint = 0
    for i, bit in enumerate(ans):
        ansint += (1 << i) * bit
    print(ansint)


if __name__ == "__main__":
    main()
