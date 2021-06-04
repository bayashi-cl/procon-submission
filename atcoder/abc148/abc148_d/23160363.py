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
    a = list(map(int, sinput().split()))
    k = 1
    ans = 0
    for ai in a:
        if ai == k:
            k += 1
        else:
            ans += 1
    if ans == n:
        ans = -1

    print(ans)


if __name__ == "__main__":
    main()
