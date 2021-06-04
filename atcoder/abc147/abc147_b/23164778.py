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
    s = sinput().strip()

    st = s[: len(s) // 2]
    ring = s[-len(s) // 2 :]

    ans = 0
    for i, j in zip(st, reversed(ring)):
        if i != j:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
