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
    v = list(map(int, sinput().split()))
    v.sort()
    m = v[0]
    for i in range(n):
        m = (v[i] + m) / 2
    print(m)


if __name__ == "__main__":
    main()
