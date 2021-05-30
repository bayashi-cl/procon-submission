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
    n, k = map(int, sinput().split())
    friend = [tuple(map(int, sinput().split())) for _ in range(n)]
    friend.sort()

    pos = 0
    mon = k
    for a, b in friend:
        if a - pos <= mon:
            mon = mon - (a - pos) + b
            pos = a
        else:
            ans = pos + mon
            break
    else:
        ans = pos + mon
    print(ans)


if __name__ == "__main__":
    main()
