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
    ans = 0
    for i in range(1, n + 1):
        if len(str(i)) % 2 == 1:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
