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
    s = sinput().strip()
    if n % 2 == 1:
        print("No")
        return

    if s[: n // 2] == s[n // 2 :]:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
