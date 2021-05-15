# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
sinput: typing.Callable[..., str] = sys.stdin.readline
INF: typing.Final[float] = float("inf")
MOD: typing.Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    a = list(map(int, sinput().split()))
    a.sort()
    if a[2] - a[1] == a[1] - a[0]:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
