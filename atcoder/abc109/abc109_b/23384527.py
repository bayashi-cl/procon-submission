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
    s = set()
    w = sinput().strip()
    prev = w[-1]
    s.add(w)

    for _ in range(n - 1):
        w = sinput().strip()
        if w[0] != prev or w in s:
            print("No")
            break
        else:
            s.add(w)
            prev = w[-1]
    else:
        print("Yes")


if __name__ == "__main__":
    main()
