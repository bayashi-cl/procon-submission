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
    H = list(map(int, sinput().split()))
    ma_h = 0
    ans = 0
    for h in H:
        if h >= ma_h:
            ans += 1
            ma_h = h
    print(ans)


if __name__ == "__main__":
    main()
