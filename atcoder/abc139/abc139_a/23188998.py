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
    S = sinput().strip()
    T = sinput().strip()

    ans = 0
    for s, t in zip(S, T):
        if s == t:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
