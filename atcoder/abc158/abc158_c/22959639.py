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
    a, b = map(int, sinput().split())
    for x in range(1, 15000):
        if x * 8 // 100 == a and x * 10 // 100 == b:
            print(x)
            break
    else:
        print(-1)


if __name__ == "__main__":
    main()
