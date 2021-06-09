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
    a = []
    for i in range(5):
        a.append(int(sinput()))
    k = int(sinput())

    for i in range(4):
        for j in range(i + 1, 5):
            if abs(a[i] - a[j]) > k:
                print(":(")
                break
        else:
            continue
        break
    else:
        print("Yay!")


if __name__ == "__main__":
    main()
