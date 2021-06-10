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
    s = list(sinput().strip())
    base = {"A", "T", "G", "C"}
    ans = 0
    for l in range(len(s)):
        for r in range(l + 1, len(s) + 1):
            fragment = s[l:r]
            if set(fragment) - base:
                continue
            ans = max(ans, len(fragment))
    print(ans)


if __name__ == "__main__":
    main()
