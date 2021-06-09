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
    s = sinput().strip()
    black = 0
    white = 0

    for i in range(len(s)):
        if i % 2 == 0:
            if s[i] == "0":
                white += 1
            else:
                black += 1
        else:
            if s[i] == "1":
                white += 1
            else:
                black += 1

    print(min(black, white))


if __name__ == "__main__":
    main()
