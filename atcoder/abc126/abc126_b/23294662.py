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
    ym, my = False, False
    if int(s[2:]) <= 12 and int(s[2:]) >= 1:
        ym = True
    if int(s[:2]) <= 12 and int(s[:2]) >= 1:
        my = True

    if ym and my:
        print("AMBIGUOUS")
    elif ym:
        print("YYMM")
    elif my:
        print("MMYY")
    else:
        print("NA")


if __name__ == "__main__":
    main()
