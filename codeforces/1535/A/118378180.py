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
    t = int(sinput())
    for i in range(t):
        s1, s2, s3, s4 = list(map(int, sinput().split()))
        if max(s1, s2) > min(s3, s4) and max(s3, s4) > min(s1, s2):
            print("YES")
        else:
            print("NO")


if __name__ == "__main__":
    main()
