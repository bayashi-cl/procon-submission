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
    _ = sinput()
    a = list(map(int, sinput().split()))

    if 0 in a:
        print(0)
        return

    ans = 1
    for ai in a:
        ans *= ai
        if ans > 10 ** 18:
            ans = -1
            break
    print(ans)


if __name__ == "__main__":
    main()
