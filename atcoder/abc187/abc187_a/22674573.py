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
    a, b = sinput().split()
    sa = 0
    for d in a:
        sa += int(d)
    sb = 0
    for d in b:
        sb += int(d)
    print(max(sa, sb))


if __name__ == "__main__":
    main()
