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
    s, t = sinput().strip().split()
    a, b = map(int, sinput().split())
    u = sinput().strip()
    if u == s:
        a -= 1
    else:
        b -= 1
    print(a, b)


if __name__ == "__main__":
    main()
