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
    h = list(map(int, sinput().split()))

    def cnt(x: int) -> int:
        res = 0
        contain = False
        for hi in h:
            if hi >= x and not contain:
                contain = True
                res += 1
            if hi < x and contain:
                contain = False
        return res

    ans = 0
    for i in range(1, max(h) + 1):
        ans += cnt(i)

    print(ans)


if __name__ == "__main__":
    main()
