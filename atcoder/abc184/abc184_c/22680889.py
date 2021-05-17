# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def judge(a, b, c, d):
    if a + b == c + d or a - b == c - d or abs(a - c) + abs(b - d) <= 3:
        return True
    else:
        return False


def main() -> None:
    r1, c1 = map(int, sinput().split())
    r2, c2 = map(int, sinput().split())

    r = r2 - r1
    c = c2 - c1

    # 0
    if (r, c) == (0, 0):
        print(0)
        return

    # 1
    if abs(c) == abs(r):
        print(1)
        return
    elif abs(r) + abs(c) <= 3:
        print(1)
        return

    # 2
    if abs(c - r) <= 3:
        print(2)
        return
    elif abs(c + r) <= 3:
        print(2)
        return
    elif abs(r) + abs(c) <= 6:
        print(2)
        return
    elif (r + c) % 2 == 0:
        print(2)
        return

    # 3
    print(3)
    return


if __name__ == "__main__":
    main()
