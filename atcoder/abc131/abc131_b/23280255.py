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
    n, l = map(int, sinput().split())
    apple = list(range(l + 1 - 1, l + n + 1 - 1))
    pie = sum(apple)
    mi_abs = INF
    for a in apple:
        if abs(a) <= mi_abs:
            mi_abs = abs(a)
            mi = a
    print(pie - mi)


if __name__ == "__main__":
    main()
