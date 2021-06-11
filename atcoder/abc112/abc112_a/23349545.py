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
    age = int(sinput())
    if age == 1:
        print("Hello World")
    else:
        a = int(sinput())
        b = int(sinput())
        print(a + b)


if __name__ == "__main__":
    main()
