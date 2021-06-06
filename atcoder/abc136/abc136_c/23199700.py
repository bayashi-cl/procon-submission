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
    H = list(map(int, sinput().split()))

    left = H[0]
    for h in H:
        if h == left:
            continue
        elif h > left:
            left = h - 1
        else:
            break
    else:
        print("Yes")
        return
    print("No")


if __name__ == "__main__":
    main()
