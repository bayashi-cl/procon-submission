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
    a = [0] * (n + 1)

    for i in range(1, n + 1):
        if i % 3 == 0 or i % 5 == 0:
            continue
        else:
            a[i] = i

    print(sum(a))


if __name__ == "__main__":
    main()
