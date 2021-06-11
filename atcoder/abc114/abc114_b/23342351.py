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
    ans = INF
    for i in range(len(s)):
        try:
            ans = min(ans, abs(753 - int(s[i : i + 3])))
        except IndexError:
            break
    print(ans)


if __name__ == "__main__":
    main()
