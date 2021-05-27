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
    a = list(map(int, sinput().split()))
    vote = sum(a)
    cnt = 0
    for ai in a:
        if ai >= vote / (4 * m):
            cnt += 1

    if cnt >= m:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
