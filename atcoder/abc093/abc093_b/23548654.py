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
    a, b, k = map(int, sinput().split())
    ans = set()
    for s in range(a, min(a + k, b + 1)):
        ans.add(s)
    for l in range(max(b - k + 1, a), b + 1):
        ans.add(l)

    ans_l = list(ans)
    ans_l.sort()
    print(*ans_l, sep="\n")


if __name__ == "__main__":
    main()
