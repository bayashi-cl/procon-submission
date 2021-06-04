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
    if n % 2 == 1:
        print(0)
        return
    ans = 0
    i = 1
    while 5 ** i <= n:
        ans += n // 5 ** i // 2
        i += 1

    print(ans)


if __name__ == "__main__":
    main()
