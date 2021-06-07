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
    n, x = map(int, sinput().split())
    l = list(map(int, sinput().split()))

    bound = [0]
    for i in range(1, n + 1):
        bound.append(bound[-1] + l[i - 1])

    print(len(list(filter(lambda a: a <= x, bound))))


if __name__ == "__main__":
    main()
