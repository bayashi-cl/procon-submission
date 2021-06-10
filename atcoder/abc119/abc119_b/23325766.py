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
    gift = 0.0
    for _ in range(n):
        x, u = sinput().split()
        if u == "JPY":
            gift += int(x)
        else:
            gift += 380000.0 * float(x)

    print(gift)


if __name__ == "__main__":
    main()
