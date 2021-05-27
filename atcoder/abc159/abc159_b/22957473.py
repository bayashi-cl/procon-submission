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


def judge(s):
    if len(s) == 1:
        return True
    m = len(s) // 2
    return s[:m] == s[-m:][::-1]


def main() -> None:
    s = sinput().strip()
    n = len(s)
    pali = True

    # print(s, file=sys.stderr)
    # print(s[: (n - 1) // 2], file=sys.stderr)
    # print(s[(n + 3) // 2 - 1 :], file=sys.stderr)

    if not judge(s):
        pali = False

    if not judge(s[: (n - 1) // 2]):
        pali = False

    if not judge(s[(n + 3) // 2 - 1 :]):
        pali = False

    if pali:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
