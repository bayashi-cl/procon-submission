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
    age = {7, 5, 3}
    x = int(sinput())
    if x in age:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
