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
    x = int(sinput())
    if x == 1:
        print(1)
        return
    ans = 1
    for b in range(2, x + 1):
        if b ** 2 > x:
            break
        p = 2
        while b ** p <= x:
            ans = max(ans, b ** p)
            p += 1
    print(ans)


if __name__ == "__main__":
    main()
