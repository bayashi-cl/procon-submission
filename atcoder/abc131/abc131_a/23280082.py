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
    if s[0] == s[1] or s[1] == s[2] or s[2] == s[3]:
        print("Bad")
    else:
        print("Good")


if __name__ == "__main__":
    main()
