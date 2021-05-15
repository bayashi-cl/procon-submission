# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
sinput: typing.Callable[..., str] = sys.stdin.readline
INF: typing.Final[float] = float("inf")
MOD: typing.Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    l = list()
    for _ in range(n):
        name, hight_ = sinput().split()
        hight = int(hight_)

        l.append((hight, name))
    l.sort()
    print(l[-2][1])


if __name__ == "__main__":
    main()
