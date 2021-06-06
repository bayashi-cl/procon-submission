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
    hand = {0, 1, 2}
    x, y = map(int, sinput().split())

    if x == y:
        print(x)
        return

    hand.remove(x)
    hand.remove(y)
    print(hand.pop())


if __name__ == "__main__":
    main()
