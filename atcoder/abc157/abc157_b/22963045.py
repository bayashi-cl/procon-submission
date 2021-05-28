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
    a = [tuple(map(int, sinput().split())) for _ in range(3)]
    card = [[False] * 3 for _ in range(3)]
    n = int(sinput())

    b = set(map(int, sys.stdin.read().split()))
    for i in range(3):
        for j in range(3):
            if a[i][j] in b:
                card[i][j] = True

    for low in card:
        if all(low):
            print("Yes")
            return

    for col in zip(*card):
        if all(col):
            print("Yes")
            return

    if (card[0][0] and card[1][1] and card[2][2]) or (
        card[0][2] and card[1][1] and card[2][0]
    ):
        print("Yes")
        return
    print("No")


if __name__ == "__main__":
    main()
