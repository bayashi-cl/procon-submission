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
    s = list(sinput().strip())
    s.sort()
    if s == ["a", "b", "c"]:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
