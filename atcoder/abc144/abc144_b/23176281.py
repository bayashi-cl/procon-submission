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
    kuku = set()
    for i in range(1, 10):
        for j in range(1, 10):
            kuku.add(i * j)
    n = int(sinput())
    if n in kuku:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
