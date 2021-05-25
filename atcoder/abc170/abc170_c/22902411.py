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
    x, n = map(int, sinput().split())
    p = set(map(int, sinput().split()))
    offset = 0

    while True:
        if x - offset not in p:
            print(x - offset)
            break

        if x + offset not in p:
            print(x + offset)
            break

        offset += 1


if __name__ == "__main__":
    main()
