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
    p = list(map(int, sinput().split()))
    cnt = 0
    for i in range(n):
        if p[i] != i + 1:
            cnt += 1

    if cnt >= 3:
        print("NO")
    else:
        print("YES")


if __name__ == "__main__":
    main()
