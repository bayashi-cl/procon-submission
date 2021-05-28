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
    n, m = map(int, sinput().split())
    req = [sinput().split() for _ in range(m)]
    for i in range(0 if n == 1 else 10 ** (n - 1), 10 ** n):
        d = str(i)
        for s, c in req:
            if d[int(s) - 1] != c:
                break
        else:
            print(d)
            break
    else:
        print(-1)


if __name__ == "__main__":
    main()
