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
    a, b = map(int, sinput().split())

    pos = list(range(1, a + 1))
    neg_ = list(range(1, b + 1))

    if a < b:
        pos[-1] += sum(neg_[a:])
    elif a > b:
        neg_[-1] += sum(pos[b:])

    neg = [-n for n in neg_]

    print(" ".join(map(str, pos + neg)))


if __name__ == "__main__":
    main()
